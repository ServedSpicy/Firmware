

#include "Main.hpp"
#include "Mixing.hpp"
#include "Display.hpp"
#include "Progress.hpp"

Recipe mixingRecipe;
u8 mixingAmount;

void prepareMixing(){

    mixingAmount = 1;
    u8 index = recipeIndex + 1;

    if(index >= recipeCount)
        index = 2;
    else
    if(index == 1)
        index = 0;
    else
        index = 1;

    Serial.print("Item: ");
    Serial.println(index);

    mixingRecipe = recipes.at(index);

    drawMixingMenu();


    const auto spices = mixingRecipe.spices;

    while(true){
        if(digitalRead(pin_down)){

            waitForButton(pin_down);

            if(mixingAmount > 0)
                mixingAmount--;

            drawMixingMenu();
            continue;
        }

        if(digitalRead(pin_up)){

            waitForButton(pin_up);

            if(mixingAmount < 255)
                mixingAmount++;

            drawMixingMenu();
            continue;
        }

        if(digitalRead(pin_left)){
            waitForButton(pin_left);
            lcd.clear();
            redraw = true;
            return;
        }

        if(digitalRead(pin_right)){
            waitForButton(pin_right);
            redraw = true;
            lcd.clear();
            return;
        }

        if(digitalRead(pin_enter)){
            waitForButton(pin_enter);
            prepareProgressMenu();
            redraw = true;
            lcd.clear();
            return;
        }
    }
}
