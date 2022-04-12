
#include "System/EEPROMWriter.hpp"

#include <EEPROM.h>


using Writer = EEPROMWriter;


void Writer::next(){
    offset++;
}


void Writer::step(byte amount){
    offset += amount;
}


void Writer::write(byte data){
    EEPROM.write(offset,data);
}


