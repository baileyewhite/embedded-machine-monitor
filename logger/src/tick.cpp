#include "tick.h"

std::ostream& operator<<(std::ostream& os, const Tick& tick)
{
    os << tick.machine_state << ',' << tick.temperature << ',' << tick.temp_status << ',' << tick.health;
    return os;
}

Tick parse_telemetry_tick(const std::string& line)
{
    std::stringstream ss(line);

    std::string machine_state;
    std::string temp_string;
    std::string temp_status;
    std::string health;

    std::getline(ss, machine_state, ',');
    std::getline(ss, temp_string, ',');
    std::getline(ss, temp_status, ',');
    std::getline(ss, health, ',');

    float temp_c = std::stof(temp_string);

    Tick tick = {
        machine_state,
        temp_c,
        temp_status,
        health
    };

    return tick;
}