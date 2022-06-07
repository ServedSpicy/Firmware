
#include <Arduino.h>
#include <EEPROM.h>
#include <deque>

#include "Display.hpp"
#include "Recipe.hpp"
#include "Debug.hpp"
#include "Main.hpp"

#include "Processes/Synchronize.hpp"
#include "Processes/Overview.hpp"
#include "Processes/Mixing.hpp"

#include "Machine/Dispenser.hpp"
#include "Machine/Integrity.hpp"
#include "Machine/Carousel.hpp"
#include "Machine/Splash.hpp"
#include "Machine/Serial.hpp"
#include "Machine/Memory.hpp"
#include "Machine/Motors.hpp"
#include "Machine/Pins.hpp"


const auto BaudRate = 9600UL;
Mode mode = Mode::Normal;


using namespace Memory;


byte recipeIndex = 0;
byte recipeCount = 0;
u16 recipeOffset = 1;

std::deque<Recipe> recipes;
std::vector<u8> sizes;
bool redraw = true;


struct RecipeData {
    Recipe recipe;
    u8 size;
};



A4988 motor_container = { 200 , 10 , 11 };
A4988 motor_dispenser = { 200 ,  8 ,  9 };


RecipeData loadRecipe(u16 address){

    using Memory::readString;

    const u8 length = EEPROM.read(address);
    const auto name = readString(address);

    address += length + 1;

    std::vector<Spice> spices;

    const u8 count = EEPROM.read(address);

    address++;

    for(byte s = 0;s < count;s++,address += 2){
        u8 spice = EEPROM.read(address);
        u8 amount = EEPROM.read(address + 1);
        spices.push_back({ spice , amount });
    }

    const u8 size = 1 + length + 1 + count * 2;

    Recipe recipe = { name , spices };

    return { recipe , size };
}




void loadNextRecipe(){

    println("Loading Next recipe");

    const auto index = recipeIndex;

    if(recipeIndex < recipeCount - 1){
        recipeIndex++;
        redraw = true;
    }

    print("Recipe Index: ");
    println(recipeIndex);

    const u8 count = sizes.size();

    if(count < 3)
        return;

    if(recipeIndex < 2)
        return;

    if(index >= recipeCount - 2)
        return;

    u16 offset = 0;

    offset += sizes.at(count - 1);
    offset += sizes.at(count - 2);
    offset += sizes.at(count - 3);

    const auto data = loadRecipe(recipeOffset + offset);

    print(" Recipe: ");
    println(data.recipe.name);

    recipes.pop_front();
    recipes.push_back(data.recipe);
    sizes.push_back(data.size);

    recipeOffset += sizes.at(count - 2);
}

void loadPreviousRecipe(){

    println("Loading previous recipe");

    if(recipeIndex > 0){
        recipeIndex--;
        redraw = true;
    }

    if(sizes.size() < 4)
        return;

    if(recipeIndex >= recipeCount - 2)
        return;

    const auto last = sizes.at(0);

    const auto data = loadRecipe(recipeOffset - last);

    recipes.pop_back();
    recipes.push_front(data.recipe);
    sizes.pop_back();

    recipeOffset -= data.size;
}



void idle(){

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

void setup(){

    using namespace Machine::Pins;

    Serial.begin(BaudRate);

    lcd.init();

    pinMode(LED_BUILTIN,OUTPUT);

    //  User Interface Buttons

    pinMode(Enter,INPUT);
    pinMode(Right,INPUT);
    pinMode(Down,INPUT);
    pinMode(Left,INPUT);
    pinMode(Up,INPUT);

    //  Photoelectric Barrier

    pinMode(13,INPUT);
    pinMode(12,INPUT);

    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,LOW);

    motor_container.begin(120,1);
    motor_dispenser.begin(120,1);

    prepareDisplay();
    drawSplashScreen();

    Carousel::home();
    Dispenser::home();


    // EEPROM.write(0,4);
    // Memory::writeString(1,"Chicken Mix1");
    // EEPROM.write(14,1);
    // EEPROM.write(15,4);
    // EEPROM.write(16,2);

    // Memory::writeString(17,"Chicken Mix2");
    // EEPROM.write(30,1);
    // EEPROM.write(31,4);
    // EEPROM.write(32,2);

    // Memory::writeString(33,"Chicken Mix3");
    // EEPROM.write(46,1);
    // EEPROM.write(47,4);
    // EEPROM.write(48,2);

    // Memory::writeString(49,"Chicken Mix4");
    // EEPROM.write(62,2);
    // EEPROM.write(63,4);
    // EEPROM.write(64,2);
    // EEPROM.write(65,66);
    // EEPROM.write(66,12);


    Overview::prepare();
}

void loop(){
    idle();
}
