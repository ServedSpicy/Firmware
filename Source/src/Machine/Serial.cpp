
#include "Machine/Serial.hpp"


bool waitForBytes(const u8 count){

    const auto time = millis();

    while(millis() - time < 1000)
        if(Serial.available() >= count)
            return true;

    return false;
}


bool waitForByte(){
    return waitForBytes(1);
}


u16 readWord(){
    return (Serial.read() << 8) | Serial.read();
}
