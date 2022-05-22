

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

void Mixing::prepare(){

    using namespace Machine::Pins;

    mixingAmount = 1;
    mixingRecipe = selectedRecipe();

    Mixing::draw();


    const auto spices = mixingRecipe.spices;

    cycle {

        if(isClicked(Down)){

            if(mixingAmount > 0)
                mixingAmount--;

            Mixing::draw();
            continue;
        }

        if(isClicked(Up)){

            if(mixingAmount < 255)
                mixingAmount++;

            Mixing::draw();
            continue;
        }

        if(isClicked(Left)){
            clearScreen();
            redraw = true;
            return;
        }

        if(isClicked(Right)){
            redraw = true;
            clearScreen();
            return;
        }

        if(isClicked(Enter)){
            Progress::prepare();
            redraw = true;
            clearScreen();
            return;
        }
    }
}


void Mixing::draw(){

    clearScreen();

    lcd.setCursor(0,0);
    lcd.print(">> ");
    lcd.print(mixingRecipe.name);

    lcd.setCursor(0,2);
    lcd.print("Amount: ");

    drawNumber(mixingAmount);

    lcd.print(" Tsp");
}
