
#include <EEPROM.h>

#include "Display.hpp"
#include "Debug.hpp"
#include "Main.hpp"

#include "Processes/Synchronize.hpp"
#include "Processes/Overview.hpp"
#include "Processes/Mixing.hpp"

#include "Machine/Integrity.hpp"
#include "Machine/Memory.hpp"
#include "Machine/Pins.hpp"



void Overview::prepare(){

    Integrity::checkEEPROM();


    recipeCount = EEPROM.read(0);

    print("Recipes: ");
    println(recipeCount);

    for(byte r = 0;r <= 2;r++){

        if(recipeIndex + r >= recipeCount)
            continue;

        byte size = recipeOffset;

        auto name = Memory::readString(recipeOffset);
        byte nameLength = EEPROM.read(recipeOffset);

        print("Name Length: ");
        println(nameLength);

        recipeOffset += nameLength; // Skip name offset
        recipeOffset++;

        print("Name: ");
        println(name);

        byte spiceCount = EEPROM.read(recipeOffset);
        recipeOffset++; // Skip spices offset

        print("Spices: ");
        println(spiceCount);

        std::vector<Spice> spices;

        for(byte s = 0;s < spiceCount;s++,recipeOffset += 2){

            byte spice = EEPROM.read(recipeOffset);
            byte amount = EEPROM.read(recipeOffset + 1);

            print("Spice: ");
            print(spice);
            print(" Amount: ");
            println(amount);

            spices.push_back({ spice , amount });
        }

        size = recipeOffset - size;

        recipes.push_back({ name , spices });
        sizes.push_back(size);
    }

    print("Deque: ");
    println(recipes.size());

    recipeOffset = 1;

    Integrity::defuseEEPROM();
}


void Overview::idle(){

    using namespace Machine::Pins;

    println("Idling");

    drawRecipeList();

    cycle {

        if(ping())
            break;

        if(
            digitalRead(Right) ||
            digitalRead(Left) ||
            digitalRead(Down) ||
            digitalRead(Up)
        ){
            mode = Mode::Normal;
            break;
        }

        delay(10);
    }

    switch(mode){
    case Normal:

        println("Normal work mode started!");

        if(digitalRead(Down)){
            waitForButton(Down);
            loadNextRecipe();
            return;
        }

        if(digitalRead(Up)){
            waitForButton(Up);
            loadPreviousRecipe();
            return;
        }

        if(digitalRead(Left)){
            waitForButton(Left);
            Mixing::prepare();
            return;
        }

        if(digitalRead(Right)){
            waitForButton(Right);
            Mixing::prepare();
            return;
        }

        return;
    case Synchronizing:

        if(!synchronize()){
            println("Failed to synchronize!");
            drawSynchronizationFailed();
        } else {

            recipeIndex = 0;
            recipeCount = 0;
            recipeOffset = 1;
            redraw = true;
            recipes.clear();
            sizes.clear();

            Overview::prepare();
        }

        redrawRecipeList();

        return;
    case Debug:

        debug();

        return;
    }
}
