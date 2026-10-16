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

    Tick tick = {
        *machine_state,
        temp_c,
        *temp_status,
        *health
    };

    return tick;
}