#ifndef Header_Macros
#define Header_Macros


#define forRange(from,to,index) \
    for(size_t (index) = (from);(index) < (to);(index)++)


#define iterate(times) \
    for(size_t _index = 0;_index < (times);_index++)


#define loopWithTimeout(timeout)            \
                                            \
        const auto start = millis();        \
                                            \
        while(millis() - start < (timeout)) \

#endif
