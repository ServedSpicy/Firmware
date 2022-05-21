

#include "Processes/Resetting.hpp"
#include "Display.hpp"


void Resetting::prepare(){

    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("  Memory Corrupted  ");
    lcd.setCursor(0,2);
    lcd.print("   Resetting  ...   ");

    delay(1000);
}
