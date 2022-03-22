
#include <EEPROM.h>

#include "Main.hpp"
#include "Debug.hpp"
#include "Processes/Overview.hpp"
#include "Machine/Memory.hpp"



void Overview::prepare(){

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
}
