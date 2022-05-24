

#include "Processes/Progress.hpp"
#include "Processes/Mixing.hpp"

#include "Machine/Motors.hpp"
#include "Machine/Pins.hpp"

#include "Display.hpp"
#include "Debug.hpp"
#include "Main.hpp"


u8 progress = 0;
u16 total = 0;

void gotoContainer(u8);

void Progress::prepare(){

    using namespace Machine::Pins;

    progress = 0;

    Progress::draw();
    Progress::next();

    cycle {

        if(isClicked(Enter)){
            drawAbort();
            return;
        }

        if(!digitalRead(13)){

            progress++;

            if(progress >= mixingRecipe.spices.size()){
                drawFinished();
                return;
            }


            Progress::draw();

            delay(400);

            Progress::next();
        }



        motor_container.nextAction();
    }
}

void Progress::draw(){

    clearScreen();

    lcd.setCursor(0,0);
    lcd.print(">> ");
    lcd.print(mixingRecipe.name);

    lcd.setCursor(0,2);
    lcd.print("Progress: ");

    if(progress < 10)
        lcd.print(" ");

    lcd.print(progress);

    lcd.print(" / ");

    lcd.print(mixingRecipe.spices.size());
}


void Progress::next(){

    const auto spice = mixingRecipe.spices.at(progress);

    const auto
        container = spice.spice,
        factor = spice.amount;

    print("Next Spice : ");
    print(container);
    print(" | ");
    println(factor);

    total = mixingAmount * factor;

    gotoContainer(container);
}


void gotoContainer(u8 index){

    // Check if already at position

    motor_container.setRPM(100);
    motor_container.setSpeedProfile(BasicStepperDriver::CONSTANT_SPEED);
    motor_container.move(999999);
    println("Done Moving");
    // motor_container.startMove(99999);
}
