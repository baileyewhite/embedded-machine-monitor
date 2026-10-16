#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <optional>

struct Tick
{
    std::string machine_state;
    float temperature;
    std::string temp_status;
    std::string health;
};

std::ostream& operator<<(std::ostream& os, const Tick& tick);

std::optional<Tick> parse_telemetry_tick(const std::string& line);