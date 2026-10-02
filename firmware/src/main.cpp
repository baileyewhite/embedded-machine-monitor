#include <cstdio>
#include <string>

#include "temp.h"
#include "telemetry.h"

#include "pico/stdlib.h"
#include "hardware/adc.h"

int main()
{
    stdio_init_all();
    adc_init();

    adc_set_temp_sensor_enabled(true);

    adc_select_input(4);

    // constexpr to allow this value to be computed at compile time
    constexpr float temp_conversion_factor = 3.3f / 4096.0f;

    int tick = 1;

    while(true)
    {
        uint16_t adc_temp = adc_read();
        float temp_volt = adc_temp * temp_conversion_factor;
        float celsius_temp = convert_volt_to_temp(temp_volt);
        float fahr_temp = convert_celsius_to_fahrenheit(celsius_temp);
        std::string temp_status = temperature_telcheck(celsius_temp);
        
        printf("Tick: %d | ADC: %d | Voltage: %.2f | Temp: %.2f °C = %.2f °F | Status: %s\n", tick, adc_temp, temp_volt, celsius_temp, fahr_temp, temp_status.c_str());
        tick++;
        sleep_ms(1000);
    }
}