#ifndef Header_Serial
#define Header_Serial

#include <Arduino.h>


bool waitForBytes(u8 count);
bool waitForByte();

u16 readWord();

#endif
