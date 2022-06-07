
#include <cmath>

#include "Machine/Carousel.hpp"
#include "Machine/Motors.hpp"
#include "Machine/Sensors.hpp"


u8 position = 0;


void moveBy(int);


void Carousel::moveTo(byte container){

    using std::abs;

    // motor_container.setRPM(100);
    // motor_container.setSpeedProfile(BasicStepperDriver::CONSTANT_SPEED);
    // motor_container.move(999999);


    u8 clockwise =
        position - container;

    if(abs(clockwise) < 8)
        clockwise = - clockwise;

    moveBy(clockwise);
}


void moveBy(int stations){

    using std::abs;

    const int direction = stations / abs(stations);
    stations = abs(stations);

    motor_container.startMove(direction * 9999);

    while(stations > 0){


        // Move off current flap

        while(sensor_container.isOn()){
            const auto wait = motor_container.nextAction();
            delay(wait);
        }

        // Move to next flap

        while(!sensor_container.isOn()){
            const auto wait = motor_container.nextAction();
            delay(wait);
        }

        position += direction;
        stations--;
    }

    motor_container.stop();
}



void Carousel::home(){

    const bool alreadyAtFlap = sensor_homing.isOn();


    // Move before homing flap

    if(alreadyAtFlap){

        motor_container.startMove(-9999);

        while(sensor_homing.isOn()){
            const auto wait = motor_container.nextAction();
            delay(wait);
        }
    }


    // Find homing flap

    if(!alreadyAtFlap){

        motor_container.startMove(9999);

        while(!sensor_homing.isOn()){
            const auto wait = motor_container.nextAction();
            delay(wait);
        }
    }

    motor_container.stop();

    position = 0;
}
