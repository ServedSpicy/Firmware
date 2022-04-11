#ifndef Header_Recipe
#define Header_Recipe

#include <Arduino.h>
#include <vector>

#include "Spice.hpp"


struct Recipe {

    /**
     * @brief Name to display in menus.
     */

    String name;


    /**
     * @brief List of spice container Ids & amounts.
     */

    std::vector<Spice> spices;
};


#endif
