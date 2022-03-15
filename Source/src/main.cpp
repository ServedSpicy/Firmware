
#include <Arduino.h>
#include <EEPROM.h>

#include "Memory.hpp"


#define cycle while(true)


enum Mode { Normal , Synchronizing , Debug };


const auto BaudRate = 9600UL;
Mode mode = Mode::Normal;


using namespace Memory;


void test(){
    digitalWrite(LED_BUILTIN,HIGH);
}

template <typename Type>
void print(Type value){
    // Serial.println(value);
}



inline bool ping(){

    Serial.write(1);

    unsigned long startTime = millis();

    while(millis() - startTime < 10){
        if(Serial.available()){

            byte b = Serial.read();

            if(b == 49){
                mode = Mode::Synchronizing;
                print("Sync");
                return true;
            }

            if(b == 50){
                mode = Mode::Debug;
                print("Debugging");
                return true;
            }

            return false;
        }
    }

    return false;
}



bool waitForBytes(byte count){

    auto time = millis();

    while(millis() - time < 1000)
        if(Serial.available() >= count)
            return true;

    return false;
}

bool waitForByte(){
    return waitForBytes(1);
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
    print(bytes);

    return true;
}

void debug(){

    Serial.println("Printing EERPOM:");
    Serial.println("------------------------");

    for(int offset = 0;offset < 1024;offset++){

        if(offset % 8 == 0)
            Serial.println();

        auto value = EEPROM.read(offset);

        if(value < 10){
            Serial.print("  ");
        } else
        if(value < 100){
            Serial.print(" ");
        }

        Serial.print(value);
        Serial.print(" ");


    }

    Serial.println();

    Serial.println("------------------------");
}

void idle(){

    cycle {

        if(ping())
            break;

        // TODO: Check if buttons are pressed

        print("Cycle");

        delay(10);
    }

    switch(mode){
    case Normal:

        return;
    case Synchronizing:

        if(!synchronize())
            print("Failed to synchronize!");

        return;
    case Debug:

        debug();

        return;
    }
}

void setup(){

    Serial.begin(BaudRate);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
    idle();
}
