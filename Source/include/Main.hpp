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

#endif
