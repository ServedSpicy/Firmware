#ifndef Header_Memory
#define Header_Memory


#include <Arduino.h>
#include <EEPROM.h>


namespace Memory {

    /**
     * @brief Write a string to the EEPROM
     * @warning The string length must not exceed 255 characters
     *
     * @param address Start position for writing
     * @param string
     */

    void writeString(int address,const String & string);


    /**
     * @brief Reads a string from the EEPROM
     * @warning The string length must not exceed 255 characters
     *
     * @param address Start position to read from
     * @return String
     */

    String readString(int address);
}

#endif
