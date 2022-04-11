
#include <Arduino.h>
#include <EEPROM.h>

#include "Processes/Synchronize.hpp"
#include "Debug.hpp"
#include "Machine/Serial.hpp"
#include "Main.hpp"
#include "System/Macros.hpp"
#include "System/EEPROMWriter.hpp"


bool readResponse(){

    const auto response = Serial.read();

    switch(response){
    case 49:
        mode = Mode::Synchronizing;
        println("Sync");
        return true;
    case 50:
        mode = Mode::Debug;
        println("Debugging");
        return true;
    }

    return false;
}

bool ping(){

    Serial.write(1);

    loopWithTimeout(10)
        if(Serial.available())
            return readResponse();

    return false;
}


bool synchronize(){

    if(!waitForBytes(2))
        return false;

    test();

    const auto bytes = readWord();

    EEPROMWriter writer { 0 };

    iterate(bytes){

        if(!waitForByte())
            return false;

        writer.write(Serial.read());
        writer.next();
    }

    print("Bytes: ");
    println(bytes);

    delay(200);
    reset();

    return true;
}
