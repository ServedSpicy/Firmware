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


void prepareDisplay(){
    lcd.backlight();
    lcd.clear();
}

void drawRecipeList(){

    Serial.print("Redrawing: ");
    Serial.println(redraw);

    delay(100);

    // lcd.home();

    if(recipeCount > 0){

        if(redraw){
            lcd.setCursor(0,0);
            lcd.print("Recipe List Menu");
        }

        byte count = recipeCount;

        if(recipeIndex > 1)
            count -= recipeIndex;

        if(count > 3)
            count = 3;

        Serial.print("Count To Show: ");
        Serial.println(count);

        if(redraw)
            for(byte r = 0;r < 3;r++){
                lcd.setCursor(1,r + 1);
                lcd.print("                   ");
                lcd.setCursor(1,r + 1);

                if(r < count){
                    u8 offset = r;

                    if(recipeIndex > 1)
                        offset += recipeIndex - 1;


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
        lcd.setCursor(0,0);
        lcd.print("  No Recipes Found  ");
        // lcd.setCursor(0,0);
        // lcd.print("                    ");
        lcd.setCursor(0,2);
        lcd.print("   Please Use the   ");
        lcd.setCursor(0,3);
        lcd.print("    Configurator    ");
    }

    redraw = false;
}

void drawMainMenu(){


    lcd.home();

}


