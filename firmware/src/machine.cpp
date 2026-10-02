#include "machine.h"

int8_t init_button()
{
    if(cyw43_arch_init())
        return -1;
    
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    return 0;
}

int8_t read_button()
{
    bool button_pressed = !gpio_get(BUTTON_PIN);

    if (button_pressed)
        return 1;
    else
        return 0;
}

void button_led(const int button_status)
{
    if ( button_status == 1)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    else
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
}

std::string read_machine_state(const int status)
{
    if (status == 1)
        return "RUNNING";
    else
        return "STOPPED";
}
