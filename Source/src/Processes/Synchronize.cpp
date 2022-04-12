
#include <Arduino.h>
#include <EEPROM.h>

#include "Processes/Synchronize.hpp"
#include "Machine/Protocol.hpp"
#include "Machine/Serial.hpp"
#include "System/EEPROMWriter.hpp"
#include "System/Macros.hpp"
#include "Debug.hpp"
#include "Main.hpp"


bool readResponse(){

    using Machine::Protocol;

    const auto response = Serial.read();

    switch(response){
    case Protocol::StartSynchronization:
        mode = Mode::Synchronizing;
        println("Sync");
        return true;
    case Protocol::PrintDebugInformation:
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
