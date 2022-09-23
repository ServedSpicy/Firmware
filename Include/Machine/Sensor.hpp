
#include <Arduino.h>


class Sensor {

    private:

       u8 pin;


    public:

        Sensor(u8 pin);

        bool isOn() const;
};
