#pragma once

#include <string>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

const uint BUTTON_PIN = 14;

int8_t init_button();

int8_t read_button();

void button_led(const int button_status);

std::string read_machine_state(const int status);