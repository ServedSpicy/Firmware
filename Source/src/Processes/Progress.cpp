

#include "Processes/Progress.hpp"
#include "Processes/Mixing.hpp"

#include "Machine/Pins.hpp"

#include "Display.hpp"
#include "Main.hpp"


u8 progress = 0;

void Progress::prepare(){

    using namespace Machine::Pins;

    progress = 0;

    Progress::draw();

    cycle {

        if(isClicked(Enter)){
            drawAbort();
            return;
        }
    }
}

void Progress::draw(){

    clearScreen();

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
