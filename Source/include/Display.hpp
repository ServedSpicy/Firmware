#ifndef Header_Display
#define Header_Display


#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


extern LiquidCrystal_I2C lcd;
extern byte index;

void drawList();

void drawMainMenu();

void drawRecipeList();

void prepareDisplay();


#endif
