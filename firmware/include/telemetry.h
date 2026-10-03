#pragma once

#include <string>

std::string temperature_telcheck(float temp);

std::string machine_health_check(std::string temp_check, bool running);