#ifndef Header_Main
#define Header_Main


#include <deque>
#include <Arduino.h>

#include "Recipe.hpp"

enum Mode { Normal , Synchronizing , Debug };

extern Mode mode;

void reset();

extern std::deque<Recipe> recipes;

extern byte recipeIndex;
extern byte recipeCount;
extern bool redraw;


inline void waitForButton(u8 pin){
    while(digitalRead(pin))
        delay(1);
}

#endif
