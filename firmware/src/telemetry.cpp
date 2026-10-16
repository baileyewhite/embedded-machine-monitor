#include "telemetry.h"

TempStatus temperature_telcheck(float temp)
{
    // based on celsius value
    if(temp > 10.0f && temp < 25.0f)
        return TempStatus::Normal;
    else if(temp > 4.0f && temp < 40.0f)
        return TempStatus::Warning;
    else
        return TempStatus::Critical;
}


Health machine_health_check(TempStatus temp_check, bool running)
{
    if(running)
    {
        if(temp_check == TempStatus::Normal)
            return Health::Healthy;
        else if(temp_check == TempStatus::Warning)
            return Health::Warning;
        else if(temp_check == TempStatus::Critical)
            return Health::Fault;
        else
            return Health::RunningFallback;
    }

    else
    {
        if(temp_check == TempStatus::Normal)
            return Health::Idle;
        else if(temp_check == TempStatus::Warning)
            return Health::Warning;
        else if(temp_check == TempStatus::Critical)
            return Health::Investigate;
        else
            return Health::StoppedFallback;
    }
}