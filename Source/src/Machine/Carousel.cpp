
#include "Machine/Carousel.hpp"
#include "Machine/Motors.hpp"


const u8 homeTimout = 100;


void Carousel::moveTo(byte container){

    // motor_container.setRPM(100);
    // motor_container.setSpeedProfile(BasicStepperDriver::CONSTANT_SPEED);
    // motor_container.move(999999);

}

void Carousel::home(){


    if(digitalRead(13)){
        motor_container.startMove(9999);

        while(digitalRead(13)){
            const auto wait = motor_container.nextAction();
            delay(wait);
        }
    }

    motor_container.startMove(9999);


}
