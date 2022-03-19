#include "Display.hpp"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


#include "Main.hpp"
#include "Mixing.hpp"
#include "Progress.hpp"

LiquidCrystal_I2C lcd(0x27,20,4);


void drawList(){
    for(byte r = 0;r <= 4;r++)
        ;
}


void prepareDisplay(){
    lcd.backlight();
    lcd.clear();
}

void drawRecipeList(){

    Serial.print("Redrawing: ");
    Serial.println(redraw);

    delay(100);

    if(recipeCount > 0){

        lcd.setCursor(0,0);
        lcd.print("Recipe List Menu");

        byte count = 3;

        // if(recipeIndex == 0)
        //     count = 2;

        if(recipeIndex >= recipeCount - 1)
            count = 2;

        if(count > recipeCount)
            count = recipeCount;

        Serial.print("Count To Show: ");
        Serial.println(count);

        if(redraw)
            for(byte r = 0;r < 3;r++){
                lcd.setCursor(2,r + 1);
                lcd.print("                  ");
                lcd.setCursor(2,r + 1);

                Serial.print(r);
                Serial.print(" : ");
                Serial.println(count);

                if(r + 1 <= count){

                    u8 offset = r;

                    if(recipeIndex > 1)
                        offset += recipeIndex - 2;

                    // if(recipeIndex + 1 == recipeCount)
                    //     offset += 1;


                    lcd.print(recipes.at(offset).name);
                }
            }

        lcd.setCursor(0,1);
        lcd.print(' ');
        lcd.setCursor(0,2);
        lcd.print(' ');
        lcd.setCursor(0,3);
        lcd.print(' ');
        lcd.setCursor(0,recipeIndex == recipeCount ? 3 : recipeIndex == 0 ? 1 : 2);
        lcd.print(">");
    } else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("  No Recipes Found  ");
        lcd.setCursor(0,2);
        lcd.print("   Please Use the   ");
        lcd.setCursor(0,3);
        lcd.print("    Configurator    ");
    }

    redraw = false;
}

void drawMixingMenu(){

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print(">> ");
    lcd.print(mixingRecipe.name);

    lcd.setCursor(0,2);
    lcd.print("Amount: ");

    if(mixingAmount < 10)
        lcd.print("  ");
    else
    if(mixingAmount < 100)
        lcd.print(" ");

    lcd.print(mixingAmount);

    lcd.print(" Tsp");

}

void drawProgressMenu(){
     lcd.clear();

    lcd.setCursor(0,0);
    lcd.print(">> ");
    lcd.print(mixingRecipe.name);

    lcd.setCursor(0,2);
    lcd.print("Progress: ");

    if(progress < 10)
        lcd.print(" ");

    lcd.print(progress);

    lcd.print(" / ");

    lcd.print(mixingRecipe.spices.size());
}


void drawAbort(){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("      Aborting      ");
    lcd.setCursor(0,2);
    lcd.print("       Mixing       ");
    delay(2400);
}
