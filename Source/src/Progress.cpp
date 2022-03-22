

#include "Processes/Progress.hpp"
#include "Display.hpp"
#include "Main.hpp"
#include "Machine/Pins.hpp"


u8 progress = 0;

void prepareProgressMenu(){

    progress = 0;

    drawProgressMenu();


    while(true){

        if(digitalRead(pin_enter)){
            waitForButton(pin_enter);

            drawAbort();

            return;
        }
    }
}