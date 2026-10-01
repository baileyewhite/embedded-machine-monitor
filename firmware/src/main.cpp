#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main()
{
    stdio_init_all();
    adc_init();

    adc_set_temp_sensor_enabled(true);

    adc_select_input(4);

    int tick = 1;

    while(true)
    {
        uint16_t temp = adc_read();
        
        printf("Embedded Machine Monitor alive - %d - Temperature: %d\n", tick, temp);
        tick++;
        sleep_ms(1000);
    }
}