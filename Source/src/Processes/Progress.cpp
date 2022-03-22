

#include "Processes/Progress.hpp"
#include "Display.hpp"
#include "Main.hpp"
#include "Machine/Pins.hpp"


u8 progress = 0;

void prepareProgressMenu(){

    progress = 0;

    drawProgressMenu();

    cycle {

        if(isClicked(pin_enter)){
            drawAbort();
            return;
        }
    }
}
