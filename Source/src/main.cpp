
#include <Arduino.h>
#include <EEPROM.h>
#include <deque>

#include "Memory.hpp"
#include "Debug.hpp"
#include "Display.hpp"
#include "Serial.hpp"
#include "Synchronize.hpp"
#include "Main.hpp"
#include "Recipe.hpp"



const byte
    pin_enter = 7 ,
    pin_right = 6 ,
    pin_left = 5 ,
    pin_down = 4 ,
    pin_up = 3 ;


#define cycle while(true)



const auto BaudRate = 9600UL;
Mode mode = Mode::Normal;


using namespace Memory;


byte recipeIndex = 0;
byte recipeCount = 0;
static int16_t recipeOffset = 1;





std::deque<ListEntry> recipes;
bool reverse = false;

void prepareRecipeList(){

    recipeCount = EEPROM.read(0);

    print("Recipes: ");
    println(recipeCount);

    for(byte r = 0;r <= 3;r++){

        if(recipeIndex + r >= recipeCount)
            continue;

        byte size = recipeOffset;

        auto name = Memory::readString(recipeOffset);
        byte nameLength = EEPROM.read(recipeOffset);
        print("Name Length: ");
        println(nameLength);
        recipeOffset += nameLength; // Skip name offset
        recipeOffset++;
        // byte spiceCount = EEPROM.read(recipeOffset);
        // recipeOffset++;

        // Spice spices[spiceCount];

        print("Name: ");
        println(name);

        byte spices = EEPROM.read(recipeOffset);
        recipeOffset += spices * 2;
        recipeOffset++; // Skip spices offset

        print("Spices: ");
        println(spices);

        // for(byte s = 0;s <= spiceCount;s++,recipeOffset += 2){
        //     byte spice = EEPROM.read(recipeOffset);
        //     byte amount = EEPROM.read(recipeOffset + 1);
        //     spices[s] = { spice , amount };
        // }

        size = recipeOffset - size;

        if(reverse){

            if(recipes.size() > 3)
                recipes.pop_back();

            recipes.push_front({ name , size });

        } else {

            if(recipes.size() > 3)
                recipes.pop_front();

            recipes.push_back({ name , size });
        }
        // recipes[r] = Recipe(name,spices);
    }
}



void idle(){

    println("Idling");

    prepareRecipeList();

    drawRecipeList();

    cycle {

        if(ping())
            break;

        if(
            digitalRead(pin_down) ||
            digitalRead(pin_up) ||
            digitalRead(pin_right) ||
            digitalRead(pin_left)
        ){
            mode = Mode::Normal;
            break;
        }

        delay(10);
    }

    switch(mode){
    case Normal:

        println("Normal work mode started!");

        drawMainMenu();

        while(true){
            delay(400);
            println(">");
        }

        return;
    case Synchronizing:

        if(!synchronize())
            println("Failed to synchronize!");

        return;
    case Debug:

        debug();

        return;
    }
}

void setup(){

    Serial.begin(BaudRate);

    lcd.init();

    pinMode(LED_BUILTIN,OUTPUT);

    //  User Interface Buttons

    pinMode(pin_enter,INPUT);
    pinMode(pin_right,INPUT);
    pinMode(pin_down,INPUT);
    pinMode(pin_left,INPUT);
    pinMode(pin_up,INPUT);

    //  Photoelectric Barrier

    pinMode(12,INPUT);

    EEPROM.write(0,4);
    Memory::writeString(1,"Chicken Mix1");
    EEPROM.write(14,1);
    EEPROM.write(15,4);
    EEPROM.write(16,2);

    Memory::writeString(17,"Chicken Mix2");
    EEPROM.write(30,1);
    EEPROM.write(31,4);
    EEPROM.write(32,2);

    Memory::writeString(33,"Chicken Mix3");
    EEPROM.write(46,1);
    EEPROM.write(47,4);
    EEPROM.write(48,2);

    Memory::writeString(49,"Chicken Mix4");
    EEPROM.write(62,1);
    EEPROM.write(63,4);
    EEPROM.write(64,2);
}

void loop(){
    idle();
}
