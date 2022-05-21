#ifndef Header_Display
#define Header_Display


#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


extern LiquidCrystal_I2C lcd;

void drawList();

void drawRecipeList();

void drawSynchronizationFailed();

void prepareDisplay();

void drawAbort();

void drawNumber(u8 number);

#endif
