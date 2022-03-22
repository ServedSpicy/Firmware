

#include "Main.hpp"
#include "Processes/Mixing.hpp"
#include "Display.hpp"
#include "Processes/Progress.hpp"
#include "Debug.hpp"
#include "Machine/Pins.hpp"

Recipe mixingRecipe;
u8 mixingAmount;


auto dequeIndex() -> u8 {

    if(recipeIndex + 1 >= recipeCount)
        return recipeCount - 1;

    if(recipeIndex == 0)
        return 0;

    return 1;
}

auto selectedRecipe() -> Recipe {

    const auto index = dequeIndex();

    print("Item: ");
    println(index);

    return recipes.at(index);
}

void prepareMixing(){

    mixingAmount = 1;
    mixingRecipe = selectedRecipe();

    drawMixingMenu();


    const auto spices = mixingRecipe.spices;

    cycle {
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
