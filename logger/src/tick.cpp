#include "tick.h"

std::ostream& operator<<(std::ostream& os, const Tick& tick)
{
    os << machine_state_to_string(tick.machine_state) << ',' << tick.temperature << ',' << temp_status_to_string(tick.temp_status) << ',' << health_to_string(tick.health);
    return os;
}

template <typename EnumType, typename Converter>
std::optional<EnumType> read_enum_field(
    std::stringstream& ss,
    Converter converter)
{
    std::string text;

    if (!std::getline(ss, text, ','))
        return std::nullopt;

    return converter(text);
}

/*
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
*/

std::optional<Tick> parse_telemetry_tick(const std::string& line)
{   
    std::stringstream ss(line);

    std::string temp_string;
    std::string garbage;

    float temp_c;

    auto machine_state = read_enum_field<MachineState>(ss, string_to_machine_state);
    if(!machine_state)
        return std::nullopt;

    if (!std::getline(ss, temp_string, ','))
        return std::nullopt;

    auto temp_status = read_enum_field<TempStatus>(ss, string_to_temp_status);
    if(!temp_status)
        return std::nullopt;

    auto health = read_enum_field<Health>(ss, string_to_health);
    if(!health)
        return std::nullopt;

    if (std::getline(ss, garbage, ','))
        return std::nullopt;

    try
    {
        temp_c = std::stof(temp_string);
    }
    catch(const std::invalid_argument&)
    {
        return std::nullopt;
    }
    catch(const std::out_of_range&)
    {
        return std::nullopt;
    }

    //bool line_valid = check_serial_line_validity(machine_state, temp_c, temp_status, health);   

    /*
    if (!line_valid)
        return std::nullopt;
    */

    Tick tick = {
        *machine_state,
        temp_c,
        *temp_status,
        *health
    };

    return tick;
}