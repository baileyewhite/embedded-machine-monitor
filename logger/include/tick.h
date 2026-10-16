#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <optional>

#include "telemetry_enums.h"

struct Tick
{
    MachineState machine_state;
    float temperature;
    TempStatus temp_status;
    Health health;
};

std::ostream& operator<<(std::ostream& os, const Tick& tick);

std::optional<Tick> parse_telemetry_tick(const std::string& line);