#ifndef ADC_H
#define ADC_H

#include "pico/stdlib.h"

class ADC {
public:
    ADC(uint gpioPin);
    int read();
    int readAvg(int avgVal);

private:
    uint _pin;
    uint _channel;
    void init();
};
#endif // ADC_H