
#include <Arduino.h>

#include "Machine/Memory.hpp"


void Memory::writeString(int address,const String & string){

    const byte length = string.length();

    EEPROM.write(address,length);

    address++;

    for(byte offset = 0;offset < length;address++,offset++)
        EEPROM.write(address,string[offset]);
}


String Memory::readString(int address){

    const byte length = EEPROM.read(address);

    address++;

    char chars[length + 1];

    for(byte offset = 0;offset < length;address++,offset++)
        chars[offset] = EEPROM.read(address);

    chars[length] = '\0';

    return String(chars);
}
