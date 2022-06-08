
#include "Machine/Sensor.hpp"
#include "Machine/Motors.hpp"
#include "Main.hpp"


using std::vector;
using std::deque;


Mode mode = Mode::Normal;

byte
    recipeIndex = 0 ,
    recipeCount = 0 ;

u16 recipeOffset = 1;

bool redraw = true;


deque<Recipe> recipes;
vector<u8> sizes;


Sensor
    sensor_container { 0 } ,
    sensor_dispenser { 0 } ,
    sensor_homing    { 0 } ;

A4988
    motor_container = { 200 , 10 , 11 } ,
    motor_dispenser = { 200 ,  8 ,  9 } ;
