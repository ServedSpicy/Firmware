#ifndef Header_Main
#define Header_Main


#include <deque>
#include <Arduino.h>
#include <vector>

#include "Recipe.hpp"

#define cycle while(true)

enum Mode { Normal , Synchronizing , Debug };

extern Mode mode;

extern std::deque<Recipe> recipes;
extern std::vector<u8> sizes;
extern byte recipeIndex;
extern byte recipeCount;
extern u16 recipeOffset;

extern bool redraw;


inline void waitForButton(u8 pin){
    while(digitalRead(pin))
        delay(1);
}

inline bool isPressed(u8 pin){
    const auto bit = digitalPinToBitMask(pin);
    const auto port = digitalPinToPort(pin);
    return * portInputRegister(port) & bit;
}

inline bool isClicked(u8 pin){

    bool wasClicked = false;

    while(isPressed(pin)){
        wasClicked = true;
        delay(10);
    }

    return wasClicked;
}


#endif
