#include "temp.h"

float convert_volt_to_temp(float adc_volt)
{
    float temp = 27 - (adc_volt - 0.706f) / 0.00172f;
    return temp;
}

float convert_celsius_to_fahrenheit(float celsius_temp)
{
    float fahrenheit = (celsius_temp * 9.0f/5.0f) + 32;
    return fahrenheit;
}