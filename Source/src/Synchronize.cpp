
#include <Arduino.h>
#include <EEPROM.h>

#include "Synchronize.hpp"
#include "Debug.hpp"
#include "Serial.hpp"
#include "Main.hpp"



bool ping(){

    Serial.write(1);

    unsigned long startTime = millis();

    while(millis() - startTime < 10){
        if(Serial.available()){

            byte b = Serial.read();

            if(b == 49){
                mode = Mode::Synchronizing;
                println("Sync");
                return true;
            }

            if(b == 50){
                mode = Mode::Debug;
                println("Debugging");
                return true;
            }

            return false;
        }
    }

    return false;
}


bool synchronize(){

    if(!waitForBytes(2))
        return false;

    test();

    auto bytes = (Serial.read() << 8) | Serial.read();

    for(byte offset = 0;offset < bytes;offset++){

        if(!waitForByte())
            return false;

        EEPROM.write(offset,Serial.read());
    }

    print("Bytes: ");
    println(bytes);

    delay(200);

    reset();

    return true;
}
