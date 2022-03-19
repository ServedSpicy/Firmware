#include "Display.hpp"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


#include "Main.hpp"

LiquidCrystal_I2C lcd(0x27,20,4);

byte index = 0;

void drawList(){
    for(byte r = 0;r <= 4;r++)
        ;
}


void drawRecipeList(){

    lcd.backlight();
    lcd.clear();
    lcd.home();

    if(recipeCount > 0){
        lcd.print("Recipe List Menu");

        byte count = recipeCount - recipeIndex;

        if(count > 3)
            count = 3;

        Serial.print("Count To Show: ");
        Serial.println(count);

        for(byte r = 0;r < count;r++){
            lcd.setCursor(1,r + 1);
            lcd.print(recipes.at(recipeIndex + r).name);
        }

        lcd.setCursor(0,1);
        lcd.print(">");
    } else {
        lcd.setCursor(0,0);
        lcd.print("  No Recipes Found  ");
        // lcd.setCursor(0,0);
        // lcd.print("                    ");
        lcd.setCursor(0,2);
        lcd.print("   Please Use the   ");
        lcd.setCursor(0,3);
        lcd.print("    Configurator    ");
    }
}

void drawMainMenu(){

    lcd.backlight();
    lcd.home();

}


