
#include <cmath>

#include "Machine/Carousel.hpp"
#include "Machine/Motors.hpp"
#include "Machine/Sensors.hpp"

#include "Debug.hpp"


const u16 oneTurn = 200 * (130 / 18);
int8_t position = 0;


void moveBy(int);


void Carousel::moveTo(byte container){

    using std::abs;

    container += 8;

    if(container > 15)
        container -= 16;

    int8_t delta =
        container - position;

    int8_t sign =
        delta / abs(delta);

    if(abs(delta) > 8)
        delta = delta - sign * 16;

    moveBy(delta);
}


void moveBy(int stations){

    using std::abs;

    const int direction = stations / abs(stations);
    stations = abs(stations);

    const int delta = direction * (int)(oneTurn);


    motor_container.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED);
    motor_container.startMove(delta,3000000);

    while(stations > 0){

        while(sensor_container.isOn())
            motor_container.nextAction();

        while(!sensor_container.isOn())
            motor_container.nextAction();

        position += direction;

        if(position < 0)
            position += 16;

        if(position > 15)
            position -= 16;

        stations--;
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
