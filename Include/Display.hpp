#ifndef Header_Display
#define Header_Display


#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


extern LiquidCrystal_I2C lcd;

void clearScreen();

void drawRecipeList();
void redrawRecipeList();

void drawSynchronizationFailed();

void prepareDisplay();

void drawAbort();
void drawFinished();

void drawNumber(u8 number);

#endif
