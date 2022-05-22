
#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>

#include "Processes/Synchronize.hpp"
#include "Machine/Protocol.hpp"
#include "Machine/Serial.hpp"
#include "System/EEPROMWriter.hpp"
#include "System/Macros.hpp"
#include "Debug.hpp"
#include "Main.hpp"
#include "Display.hpp"


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

    loopWithTimeout(10){

        if(Serial.available())
            return readResponse();
    }

    return false;
}


bool synchronize(){

    clearScreen();

    lcd.setCursor(0,1);
    lcd.print("    Synchronizing   ");
    lcd.setCursor(0,2);
    lcd.print("           Bytes   ");

    if(!waitForBytes(2))
        return false;

    test();

    const auto bytes = readWord();

    lcd.setCursor(5,2);
    lcd.print(bytes);

    EEPROMWriter writer { 0 };

    iterate(bytes){

        if(!waitForByte())
            return false;

        writer.write(Serial.read());
        writer.next();
    }

    print("Bytes: ");
    println(bytes);

    delay(1000);

    return true;
}
