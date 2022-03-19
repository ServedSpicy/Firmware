#ifndef Header_Recipe
#define Header_Recipe

#include <Arduino.h>

#include <vector>

struct Spice {
    byte spice;
    byte amount;
};

struct Recipe {
    String name;
    std::vector<Spice> spices;
};


#endif
