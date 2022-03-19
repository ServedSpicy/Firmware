#ifndef Header_Main
#define Header_Main


#include <deque>
#include <Arduino.h>

enum Mode { Normal , Synchronizing , Debug };

extern Mode mode;

struct ListEntry {
    String name;
    byte size;
};

extern std::deque<ListEntry> recipes;

extern byte recipeIndex;
extern byte recipeCount;

#endif
