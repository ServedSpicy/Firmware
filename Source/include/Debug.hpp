#ifndef Header_Debug
#define Header_Debug


void debug();

template <typename Type>
void print(Type value){
    Serial.print(value);
}

template <typename Type>
void println(Type value){
    Serial.println(value);
}

void test();


#endif
