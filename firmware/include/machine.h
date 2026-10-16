#pragma once

#include <string>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "telemetry_enums.h"

constexpr uint BUTTON_PIN = 14;

int8_t init_button();

bool read_button();

void button_led(bool button_status);

MachineState read_machine_state(bool status);