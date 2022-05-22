#include "Display.hpp"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


#include "Main.hpp"
#include "Processes/Mixing.hpp"
#include "Processes/Progress.hpp"
#include "Debug.hpp"
#include "System/Macros.hpp"

LiquidCrystal_I2C lcd(0x27,20,4);


void drawList(){
    for(byte r = 0;r <= 4;r++)
        ;
}

void clearScreen(){
    lcd.clear();
    delay(10);
}


void prepareDisplay(){
    lcd.backlight();
    clearScreen();
}

void drawSynchronizationFailed(){
    clearScreen();
    lcd.setCursor(0,1);
    lcd.print("   Synchronization  ");
    lcd.setCursor(0,2);
    lcd.print("       Failed       ");
    delay(2000);
}

void drawNoRecipesFound(){
    clearScreen();
    lcd.setCursor(0,0);
    lcd.print("  No Recipes Found  ");
    lcd.setCursor(0,2);
    lcd.print("   Please Use the   ");
    lcd.setCursor(0,3);
    lcd.print("    Configurator    ");
}


void redrawRecipeList(){
    clearScreen();
    drawRecipeList();
}

void drawRecipeList(){

    print("Redrawing: ");
    println(redraw);

    delay(100);

    if(recipeCount > 0){

        lcd.setCursor(0,0);
        lcd.print("Recipe List Menu");

        byte count = 3;

        if(recipeIndex >= recipeCount - 1)
            count = 2;

        if(count > recipeCount)
            count = recipeCount;

        print("Count To Show: ");
        println(count);

        auto drawRecipe = [ & ](u8 index){

            const auto line = index + 1;

            lcd.setCursor(2,line);
            lcd.print("                  ");
            lcd.setCursor(2,line);

            print(index);
            print(" : ");
            println(count);

            if(line > count)
                return;

            u8 offset = index;

            if(recipeIndex > 1)
                offset += recipeIndex - 2;

            const auto recipe = recipes.at(offset);

            lcd.print(recipe.name);
        };

        if(redraw)
            forRange(0,3,r)
                drawRecipe(r);

        lcd.setCursor(0,1);
        lcd.print(' ');
        lcd.setCursor(0,2);
        lcd.print(' ');
        lcd.setCursor(0,3);
        lcd.print(' ');
        lcd.setCursor(0,recipeIndex == recipeCount ? 3 : recipeIndex == 0 ? 1 : 2);
        lcd.print(">");
    } else {
        drawNoRecipesFound();
    }

    redraw = false;
}


void drawNumber(u8 number){

    if(number < 10)
        lcd.print(" ");

    if(number < 100)
        lcd.print(" ");

    lcd.print(number);
}


void drawAbort(){
    clearScreen();
    lcd.setCursor(0,1);
    lcd.print("      Aborting      ");
    lcd.setCursor(0,2);
    lcd.print("       Mixing       ");
    delay(2400);
}
