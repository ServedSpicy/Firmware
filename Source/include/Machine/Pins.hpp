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
         *             7
         *             ▲
         *
         *      5 ◀   ▪ 3 ▶ 4
         *
         *             ▼
         *             6
         *
         */

        const pin
            Enter = 3 ,
            Right = 4 ,
            Left = 5 ,
            Down = 6 ,
            Up = 7 ;

    }
}


#endif
