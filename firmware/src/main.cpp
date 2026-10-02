#include <cstdio>
#include "temp.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main()
{
    stdio_init_all();
    adc_init();

    adc_set_temp_sensor_enabled(true);

    adc_select_input(4);

    float temp_conversion_factor = 3.3f / 4096.0f;

    int tick = 1;

    while(true)
    {
        uint16_t adc_temp = adc_read();
        float temp_volt = adc_temp * temp_conversion_factor;
        float celc_temp = convert_volt_to_temp(temp_volt);
        float fahr_temp = convert_celsius_to_fahrenheit(celc_temp);
        
        printf("Embedded Machine Monitor alive - %d - ADC Temp: %d - Voltage: %.2f - Temp: %.2f C°, %.2f F°\n", tick, adc_temp, temp_volt, celc_temp, fahr_temp);
        tick++;
        sleep_ms(1000);
    }
}