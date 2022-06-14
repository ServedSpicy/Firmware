
#include <cmath>

#include "Machine/Carousel.hpp"
#include "Machine/Motors.hpp"
#include "Machine/Sensors.hpp"

#include "Debug.hpp"


const u16 oneTurn = 200 * (130 / 18);
u8 position = 0;


void moveBy(int);


void Carousel::moveTo(byte container){

    container = 16 - container;

    using std::abs;

    // motor_container.setRPM(100);
    // motor_container.setSpeedProfile(BasicStepperDriver::CONSTANT_SPEED);
    // motor_container.move(999999);


    u8 clockwise =
        position - container;

    if(abs(clockwise) > 8)
        clockwise = - clockwise;

    moveBy(clockwise);

    print("Moved to container ");
    println(16 - container);
}


void moveBy(int stations){



    using std::abs;

    const int direction = stations / abs(stations);
    stations = abs(stations);

    print("Moving by ");
    print(stations);
    print(" ");
    print(direction);
    println(" Stations");


    // motor_container.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED);
    // motor_container.startMove((oneTurn / 16) * 2,(3000 / 16) * 2);

    // while(sensor_container.isOn())
    //     motor_container.nextAction();

    // println("Moved off");

    // while(!sensor_container.isOn())
    //     motor_container.nextAction();

    // motor_container.stop();


    // motor_container.setRPM(100);
    motor_container.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED);
    // motor_container.startMove(direction * (stations + 2) * (oneTurn / 16),(3000 / 16) * (stations + 2));
    motor_container.startMove(direction * oneTurn,3000000);

    // motor_container.rotate(360 / 16 * stations * 7.2 * direction);

    while(stations > 0){

        // motor_container.startMove(direction * 2 * (oneTurn / 16),(3000 / 16) * 2);


        // Move off current flap

        // while(!digitalRead(13)){

        while(sensor_container.isOn())
            motor_container.nextAction();

        //     const auto wait = motor_container.nextAction();

        //     print(!digitalRead(13));
        //     println(wait);
        // }


        println("Moved off flap");

        // Move to next flap

        // while(digitalRead(13))
        while(!sensor_container.isOn())
            motor_container.nextAction();

        position += direction;
        stations--;

        // if(stations == 1)
            // motor_container.startBrake();

        println("Finished Station");
    }


    motor_container.stop();
}



void Carousel::home(){

    const bool alreadyAtFlap = sensor_homing.isOn();

    if(alreadyAtFlap)
        return;

    motor_container.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED);
    motor_container.startMove(oneTurn,3000000);

    while(!sensor_homing.isOn())
        motor_container.nextAction();

    motor_container.stop();

    position = 0;
}
