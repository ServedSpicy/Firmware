
#include <Arduino.h>
#include <EEPROM.h>

#include "Debug.hpp"



void test(){
    digitalWrite(LED_BUILTIN,HIGH);
}


void debug(){

    println("Printing EERPOM:");
    println("------------------------");

    for(int offset = 0;offset < 1024;offset++){

        if(offset % 8 == 0)
            println("");

        auto value = EEPROM.read(offset);

        if(value < 10){
            print("  ");
        } else
        if(value < 100){
            print(" ");
        }

        print(value);
        print(" ");
    }

    println("");

    println("------------------------");
}
