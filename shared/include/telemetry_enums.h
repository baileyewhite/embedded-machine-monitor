#pragma once

#include <string>
#include <optional>

enum class MachineState
{
    Running,
    Stopped,
    NotAvailable,
};

std::string machine_state_to_string(MachineState state);

std::optional<MachineState> string_to_machine_state(const std::string& state_text);

enum class TempStatus
{
    Normal,
    Warning,
    Critical,
};

std::string temp_status_to_string(TempStatus status);

std::optional<TempStatus> string_to_temp_status(const std::string& status_text);

enum class Health
{
    Unknown,
    Healthy,
    Idle,
    Warning,
    Fault,
    RunningFallback,
    Investigate,
    StoppedFallback,
};

std::string health_to_string(Health status);

std::optional<Health> string_to_health(const std::string& health_text);