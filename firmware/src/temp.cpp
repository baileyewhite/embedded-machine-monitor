#include "temp.h"

float convert_volt_to_temp(float adc_volt)
{
    float temp = 27 - (adc_volt - 0.706) / 0.00172;
    return temp;
}

float convert_celsius_to_fahrenheit(float celsius_temp)
{
    float fahrenheit = (celsius_temp * 9/5) + 32;
    return fahrenheit;
}