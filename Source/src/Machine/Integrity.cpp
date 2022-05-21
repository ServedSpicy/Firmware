
#include <EEPROM.h>

#include "Machine/Integrity.hpp"
#include "Processes/Resetting.hpp"


const int loop_guard = 1023;


inline void resetEEPROM(){

    Resetting::prepare();

    for(int i = 0;i <= 1024;i++)
        EEPROM.write(i,0);
}


void Integrity::checkEEPROM(){

    const byte loops = EEPROM.read(loop_guard);

    if(loops > 1)
        resetEEPROM();

    EEPROM.write(loop_guard,1);
}

void Integrity::defuseEEPROM(){
    EEPROM.write(loop_guard,0);
}
