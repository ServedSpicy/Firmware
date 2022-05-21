#ifndef Header_LoopGuard
#define Header_LoopGuard


#include <Arduino.h>


namespace Integrity {

    /**
     * @brief Checks EEPROM and clears if
     *        it contains corrupt data.
     */

    void checkEEPROM();

    /**
     * @brief Resets loop guard to
     *        signal successful parsing
     */

    void defuseEEPROM();
}

#endif
