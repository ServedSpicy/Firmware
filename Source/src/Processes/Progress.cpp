

#include "Processes/Progress.hpp"
#include "Processes/Mixing.hpp"

#include "Machine/Pins.hpp"

#include "Display.hpp"
#include "Main.hpp"


u8 progress = 0;

void Progress::prepare(){

    progress = 0;

    Progress::draw();

    cycle {

        if(isClicked(pin_enter)){
            drawAbort();
            return;
        }
    }
}

void Progress::draw(){

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
