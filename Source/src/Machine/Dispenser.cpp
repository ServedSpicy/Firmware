
#include "Machine/Dispenser.hpp"
#include "Machine/Sensors.hpp"
#include "Machine/Motors.hpp"
#include "Machine/Carousel.hpp"


const u8 stepsHalfTurn = 20;
const u8 containerDelta = 40;


void Dispenser::intoPosition(){
    motor_dispenser.move(stepsHalfTurn);
}

void Dispenser::outOfPosition(){
    motor_dispenser.move(stepsHalfTurn);
}

void Dispenser::dispense(u16 turns){
    motor_dispenser.move(stepsHalfTurn * 2 * turns);
}

void Dispenser::home(){

    Carousel::moveTo(0);

    motor_dispenser.startMove(999);

    while(!sensor_dispenser.isOn()){
        const auto wait = motor_container.nextAction();
        delay(wait);
    }

    motor_dispenser.move(stepsHalfTurn);
}
