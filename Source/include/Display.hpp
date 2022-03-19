#ifndef Header_Display
#define Header_Display


#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


extern LiquidCrystal_I2C lcd;

void drawList();

void drawMixingMenu();

void drawRecipeList();

void prepareDisplay();


#endif
