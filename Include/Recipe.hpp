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


    /**
     * @return The combined amount of spice.
     */

    u16 amounts() const {

        u16 parts = 0;

        for(const auto & spice : spices)
            parts += spice.amount;

        return parts;
    }
};


#endif
