

#include "Processes/Progress.hpp"
#include "Processes/Mixing.hpp"

#include "Machine/Dispenser.hpp"
#include "Machine/Carousel.hpp"
#include "Machine/Motors.hpp"
#include "Machine/Pins.hpp"

#include "Display.hpp"
#include "Debug.hpp"
#include "Main.hpp"


const u8 turnsPerTeaspoon = 10;


u8 progress = 0;
u16 turns = 0;


void Progress::prepare(){

    using namespace Machine::Pins;

    progress = 0;

    Progress::draw();
    Progress::next();

    // cycle {

    //     if(isClicked(Enter)){
    //         drawAbort();
    //         return;
    //     }

    //     if(!digitalRead(13)){

    //         progress++;

    //         if(progress >= mixingRecipe.spices.size()){
    //             drawFinished();
    //             return;
    //         }


    //         Progress::draw();

    //         delay(400);

    //         Progress::next();
    //     }



    //     motor_container.nextAction();
    // }
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

    turns = turnsPerTeaspoon * mixingAmount * ((double) factor / (double) mixingRecipe.amounts());

    print("Turns : ");
    println(turns);

    Carousel::moveTo(container);

    Dispenser::intoPosition();

    Dispenser::dispense(turns);

    Dispenser::outOfPosition();

    progress++;

    Progress::draw();

    if(progress >= mixingRecipe.spices.size()){
        drawFinished();
        return;
    }

    Progress::draw();

    delay(400);

    Progress::next();
}
