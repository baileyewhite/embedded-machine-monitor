#include "pico/stdlib.h"
#include <cstdio>

int main()
{
    stdio_init_all();

    int tick = 1;

    while(true)
    {
        printf("Embedded Machine Monitor alive - %d\n", tick);
        tick++;
        sleep_ms(1000);
    }
}