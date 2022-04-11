#ifndef Header_Spice
#define Header_Spice

#include <Arduino.h>


struct Spice {

    /**
     *  @brief The position / index of the spices' container.
     *  @details
     *
     *  Container Layout:
     *
     *                  ▢ 8
     *             ▢ 7      ▢ 9
     *          ▢ 6            ▢ 10
     *       ▢ 5                  ▢ 11
     *
     *     ▢ 4                      ▢ 12
     *
     *       ▢ 3                  ▢ 13
     *          ▢ 2            ▢ 14
     *             ▢ 1      ▢ 15
     *                  ▢ 0
     *
     *
     *  Default value is 255 as there
     *  aren't that many containers.

     */

    byte spice = 255;


    /**
     *  @brief Amount of turns the dispenser skrew moves for 1 unit of spice.
     */

    byte amount = 0;


    Spice(byte spice,byte amount)
        : spice(spice)
        , amount(amount) {}
};


#endif
