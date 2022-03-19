
#include <Arduino.h>
#include <EEPROM.h>

#include "Debug.hpp"



void test(){
    digitalWrite(LED_BUILTIN,HIGH);
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
