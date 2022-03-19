#ifndef Header_Recipe
#define Header_Recipe

#include <Arduino.h>


struct Spice {
    byte spice;
    byte amount;
};

struct Recipe {
    String name;
    struct Spice spices[];
};


#endif
