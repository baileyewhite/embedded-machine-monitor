#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

const uint BUTTON_PIN = 14;

int main()
{
    // Initialize the Pico W wireless chip,
    // which also controls the onboard LED.
    if (cyw43_arch_init())
    {
        return -1;
    }

    // Configure GP14 as an input.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Hold the input HIGH when the button isn't pressed.
    gpio_pull_up(BUTTON_PIN);

    while (true)
    {
        bool button_pressed = !gpio_get(BUTTON_PIN);

        if (button_pressed)
        {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        }
        else
        {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }

        sleep_ms(10);
    }
}
