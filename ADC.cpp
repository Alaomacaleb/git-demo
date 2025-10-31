#include "ADC.h"
#include "hardware/adc.h"
#include "dbop.h"        // for C_ADC() debug macro
#include "pico/stdlib.h"

// Constructor
ADC::ADC(uint gpioPin) : _pin(gpioPin), _channel(0) {
    C_ADC("ADC constructor called");
    init();
}

// Private init() method
void ADC::init() {
    C_ADC("Initializing ADC on GPIO");


    adc_init();                 // Initialize ADC hardware
    adc_gpio_init(_pin);        // Configure GPIO for ADC

    // Determine ADC channel (GPIO26→0, 27→1, 28→2)
    if (_pin >= 26 && _pin <= 28)
        _channel = _pin - 26;
    else
        _channel = 0;           // Default to channel 0 if invalid

    adc_select_input(_channel); // Select ADC input
    C_ADC("ADC initialized on channel");
}

// Read a single ADC value (0–4095)
int ADC::read() {
    adc_select_input(_channel);
    int value = adc_read();     // 12-bit result
    return value;
}

// Read and average multiple samples
int ADC::readAvg(int avgVal) {
    if (avgVal <= 0)
        avgVal = 1;

    C_ADC("Averaging %d samples");

    int total = 0;
    for (int i = 0; i < avgVal; i++) {
        total += read();
        sleep_ms(2); // short delay between readings
    }

    int avg = total / avgVal;
    C_ADC("ADC average complete");
    return avg;
}

