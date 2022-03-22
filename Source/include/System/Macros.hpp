#ifndef Header_Macros
#define Header_Macros


#define forRange(from,to,index) \
     for(size_t (index) = (from);(index) < (to);(index)++)


#define loopWithTimeout(timeout)            \
                                            \
        const auto start = millis();        \
                                            \
        while(millis() - start < (timeout)) \

#endif
