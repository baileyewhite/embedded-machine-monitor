#include <cstdio>
#include <string>

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