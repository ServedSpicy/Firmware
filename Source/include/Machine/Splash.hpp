#ifndef Header_Splash
#define Header_Splash

#include <Arduino.h>

#include "Display.hpp"
#include "System/Macros.hpp"
#include "Machine/Version.hpp"


PROGMEM const byte panels [ 30 * 8 ] {
    128,128,128,128,128,128,131,140 ,
    128,128,128,129,131,135,159,135 ,
    128,128,128,144,152,156,159,156 ,
    128,128,128,128,128,128,152,134 ,
    144,140,143,143,129,128,128,128 ,
    131,128,159,159,159,128,128,128 ,
    152,128,159,159,159,128,128,128 ,
    129,134,158,158,144,128,128,128
};


void drawSplashScreen(){

    forRange(0,2,y)
        forRange(0,4,x){

            byte buffer[8];

            const u8 panel = (y * 4 + x);

            forRange(0,8,b)
                buffer[b] = pgm_read_byte_near(panels + panel * 8 + b);

            Serial.print(x);
            Serial.print(" ");
            Serial.print(y);
            Serial.print(" ");
            Serial.print(" ");
            Serial.println(buffer[0]);

            lcd.createChar(panel,buffer);
            lcd.setCursor(x + 8,y);
            lcd.write(panel);
        }

    lcd.setCursor(4,2);
    lcd.print("Served Spicy");
    lcd.setCursor((20 - Version.length()) * 0.5,3);
    lcd.print(Version);

    delay(2000);
}

#endif
