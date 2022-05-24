#ifndef Header_Debug
#define Header_Debug


// #define DEBUG


void debug();

template <typename Type>
void print(Type value){

    #ifdef DEBUG
       Serial.print(value);
    #endif
}

template <typename Type>
void println(Type value){

    #ifdef DEBUG
        Serial.println(value);
    #endif
}

void test();


#endif
