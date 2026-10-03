#include "telemetry.h"

std::string temperature_telcheck(float temp)
{
    // based on celsius value
    if(temp > 10.0f && temp < 25.0f)
        return "NORMAL";
    else if(temp > 4.0f && temp < 40.0f)
        return "WARNING";
    else
        return "CRITICAL";
}


std::string machine_health_check(std::string temp_check, bool running)
{
    if(running)
    {
        if(temp_check == "NORMAL")
            return "HEALTHY";
        else if(temp_check == "WARNING")
            return "WARNING";
        else if(temp_check == "CRITICAL")
            return "FAULT";
        else
            return "RUNNING FALLBACK";
    }

    else
    {
        if(temp_check == "NORMAL")
            return "IDLE";
        else if(temp_check == "WARNING")
            return "WARNING";
        else if(temp_check == "CRITICAL")
            return "INVESTIGATE";
        else
            return "STOPPED FALLBACK";
    }
}