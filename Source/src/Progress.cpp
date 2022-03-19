

#include "Progress.hpp"
#include "Display.hpp"
#include "Main.hpp"


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
