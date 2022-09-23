
#include "Machine/Sensor.hpp"


Sensor::Sensor(u8 pin)
    : pin(pin) {}


bool Sensor::isOn() const {
    return digitalRead(pin) == LOW;
}
