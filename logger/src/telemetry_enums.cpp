#include "telemetry_enums.h"

std::string machine_state_to_string(MachineState state)
{
    switch(state)
    {
        case MachineState::Running:
            return "RUNNING";
        
        case MachineState::Stopped:
            return "STOPPED";

        case MachineState::NotAvailable:
            return "N/A";
    }
    return "UNKNOWN";
}

std::optional<MachineState> string_to_machine_state(const std::string& state_text)
{
    if (state_text == "RUNNING")
        return MachineState::Running;
    else if (state_text == "STOPPED")
        return MachineState::Stopped;
    else if (state_text == "N/A")
        return MachineState::NotAvailable;
    return std::nullopt;
}

std::string temp_status_to_string(TempStatus status)
{
    switch(status)
    {
        case TempStatus::Normal:
            return "NORMAL";
        
        case TempStatus::Warning:
            return "WARNING";

        case TempStatus::Critical:
            return "CRITICAL";
    }
    return "UNKNOWN";
}

std::optional<TempStatus> string_to_temp_status(const std::string& status_text)
{
    if(status_text == "NORMAL")
        return TempStatus::Normal;
    else if(status_text == "WARNING")
        return TempStatus::Warning;
    else if(status_text == "CRITICAL")
        return TempStatus::Critical;
    return std::nullopt;
}

std::string health_to_string(Health status)
{
    switch(status)
    {
        case Health::Unknown:
            return "UNKNOWN";
        
        case Health::Healthy:
            return "HEALTHY";
        
        case Health::Idle:
            return "IDLE";

        case Health::Warning:
            return "WARNING";

        case Health::Fault:
            return "FAULT";
        
        case Health::RunningFallback:
            return "RUNNING FALLBACK";

        case Health::Investigate:
            return "INVESTIGATE";

        case Health::StoppedFallback:
            return "STOPPED FALLBACK";
    }
    return "UNKNOWN";
}

std::optional<Health> string_to_health(const std::string& health_text)
{
    if(health_text == "UNKNOWN")
        return Health::Unknown;
    else if(health_text == "HEALTHY")
        return Health::Healthy;
    else if(health_text == "IDLE")
        return Health::Idle;
    else if(health_text == "WARNING")
        return Health::Warning;
    else if(health_text == "FAULT")
        return Health::Fault;
    else if(health_text == "RUNNING FALLBACK")
        return Health::RunningFallback;
    else if(health_text == "INVESTIGATE")
        return Health::Investigate;
    else if(health_text == "STOPPED FALLBACK")
        return Health::StoppedFallback;
    return std::nullopt;
}
