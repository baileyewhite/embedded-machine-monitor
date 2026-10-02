#include "temp.h"

float convert_volt_to_temp(float adc_volt)
{
    // volts to temp conversion formula found in Raspberry Pi docs
    float temp = 27 - (adc_volt - 0.706f) / 0.00172f;
    return temp;
}

float convert_celsius_to_fahrenheit(float celsius_temp)
{
    // conversion calculation for celsius -> fahrenheit
    float fahrenheit = (celsius_temp * 9.0f/5.0f) + 32.0f;
    return fahrenheit;
}
