#ifndef EEPROM_Writer
#define EEPROM_Writer

#include <Arduino.h>


class EEPROMWriter {

    private:

        int offset;

    public:

        EEPROMWriter(int offset = 0)
            : offset(offset) {}

        void next();

        void step(byte amount = 1);

        void write(byte data);
};

#endif
