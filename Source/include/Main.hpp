#ifndef Header_Main
#define Header_Main


#include <deque>
#include <Arduino.h>

#include "Recipe.hpp"

enum Mode { Normal , Synchronizing , Debug };

extern Mode mode;

// struct ListEntry {
//     String name;
//     byte size;
// };

extern std::deque<Recipe> recipes;

extern byte recipeIndex;
extern byte recipeCount;
extern bool redraw;

const byte
    pin_enter = 7 ,
    pin_right = 6 ,
    pin_left = 5 ,
    pin_down = 4 ,
    pin_up = 3 ;

inline void waitForButton(u8 pin){
    while(digitalRead(pin))
        delay(1);
}

#endif
