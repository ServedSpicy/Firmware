

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

        if(isClicked(pin_down)){

            if(mixingAmount > 0)
                mixingAmount--;

            drawMixingMenu();
            continue;
        }

        if(isClicked(pin_up)){

            if(mixingAmount < 255)
                mixingAmount++;

            drawMixingMenu();
            continue;
        }

        if(isClicked(pin_left)){
            lcd.clear();
            redraw = true;
            return;
        }

        if(isClicked(pin_right)){
            redraw = true;
            lcd.clear();
            return;
        }

        if(isClicked(pin_enter)){
            prepareProgressMenu();
            redraw = true;
            lcd.clear();
            return;
        }
    }
}


void drawMixingMenu(){

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print(">> ");
    lcd.print(mixingRecipe.name);

    lcd.setCursor(0,2);
    lcd.print("Amount: ");

    drawNumber(mixingAmount);

    lcd.print(" Tsp");
}
