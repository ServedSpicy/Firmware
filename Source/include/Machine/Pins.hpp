#ifndef Header_Pins
#define Header_Pins

#include <Arduino.h>


namespace Machine {

    using pin = byte;


    namespace Pins {

        /**
         *  @brief Pins used for the user interface.
         *  @details
         *
         *             3
         *             ▲
         *
         *      5 ◀   ▪ 7 ▶ 6
         *
         *             ▼
         *             4
         *
         */

        const pin
            Enter = 7 ,
            Right = 6 ,
            Left = 5 ,
            Down = 4 ,
            Up = 3 ;

    }
}


#endif
