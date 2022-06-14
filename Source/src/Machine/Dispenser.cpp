
#include "Machine/Dispenser.hpp"
#include "Machine/Sensors.hpp"
#include "Machine/Motors.hpp"
#include "Machine/Carousel.hpp"

#include "Debug.hpp"


const u16 oneTurn = 200 * (42 / 8);
const u16 halfTurn = .5 * oneTurn;
// const u8 containerDelta = 40;


void Dispenser::intoPosition(){
    // motor_dispenser.setRPM(200);
    // motor_dispenser.setSpeedProfile(BasicStepperDriver::CONSTANT_SPEED);
    // motor_dispenser.move(halfTurn);
}

void Dispenser::outOfPosition(){
    // motor_dispenser.setRPM(200);
    // motor_dispenser.setSpeedProfile(BasicStepperDriver::CONSTANT_SPEED);
    // motor_dispenser.move(halfTurn);
}

void Dispenser::dispense(u16 turns){
    motor_dispenser.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED);
    motor_dispenser.startMove(-oneTurn * (turns + 1),(turns + 1) * 500);
    while(turns > 0){

       // Move off current flap

        while(sensor_dispenser.isOn()){
            const auto wait = motor_dispenser.nextAction();
        }

        // Move to next flap

        while(!sensor_dispenser.isOn()){
            const auto wait = motor_dispenser.nextAction();
        }

        turns--;
    }

    motor_dispenser.stop();
}

void Dispenser::home(){

    // Carousel::moveTo(0);

    if(sensor_dispenser.isOn())
        return;

    // motor_dispenser.setRPM(200);
    // motor_dispenser.setSpeedProfile(BasicStepperDriver::CONSTANT_SPEED);

    motor_dispenser.startMove(oneTurn,2000);


    long wait;

    do {

        wait = motor_dispenser.nextAction();

        println(wait);

    } while(!sensor_dispenser.isOn() && wait);

    println("First Part Done");

    const auto entrance = motor_dispenser.getStepsCompleted();

    do {

        wait = motor_dispenser.nextAction();

        println(wait);

    } while(sensor_dispenser.isOn() && wait);


    println("Second Part Done");

    const auto exit = motor_dispenser.getStepsCompleted();

    print("Steps: ");
    print(entrance);
    print(" ");
    println(exit);

    const auto half = .5 * ( exit - entrance );

    print("Half: ");
    println(half);

    motor_dispenser.startMove(-half);


    do {

        wait = motor_dispenser.nextAction();

        println(wait);

    } while(wait);

    // while(true){

    //     const auto wait = motor_dispenser.nextAction();

    //     if(wait <= 0)
    //         break;
    // }

    motor_dispenser.stop();
}
