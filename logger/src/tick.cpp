#include "tick.h"

std::ostream& operator<<(std::ostream& os, const Tick& tick)
{
    os << tick.machine_state << ',' << tick.temperature << ',' << tick.temp_status << ',' << tick.health;
    return os;
}

bool check_serial_line_validity(std::string machine_state,
    float temp,
    std::string temp_status,
    std::string health)
{
    if (machine_state != "RUNNING" && machine_state != "STOPPED" && machine_state != "N/A")
        return false;
    
    if (temp <= -200 || temp >= 200)
        return false;
    
    if (temp_status != "NORMAL" && temp_status != "WARNING" && temp_status != "CRITICAL")
        return false;
    
    if (health != "UNKNOWN" && health != "IDLE" && health != "HEALTHY" && health != "WARNING" &&
        health != "FAULT" && health != "RUNNING FALLBACK" && health != "INVESTIGATE" &&
        health != "STOPPED FALLBACK")
        return false;
    
    return true;
}

std::optional<Tick> parse_telemetry_tick(const std::string& line)
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

    bool line_valid = check_serial_line_validity(machine_state, temp_c, temp_status, health);   

    if (!line_valid)
    {
        std::cerr << "Error: Invalid Tick Object\n";
        return std::nullopt;
    }
    
    Tick tick = {
        machine_state,
        temp_c,
        temp_status,
        health
    };

    return tick;
}