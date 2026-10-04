#pragma once

#include <string>
#include <sstream>

struct Tick
{
    std::string machine_state;
    float temperature;
    std::string temp_status;
    std::string health;
};

std::ostream& operator<<(std::ostream& os, const Tick& tick);

Tick parse_telemetry_tick(const std::string& line);