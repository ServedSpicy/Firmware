#ifndef Header_Progress
#define Header_Progress

#include <Arduino.h>


extern u8 progress;

namespace Progress {

    void prepare();
    void draw();
}


#endif
