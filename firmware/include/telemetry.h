#pragma once

#include <string>
#include "telemetry_enums.h"

TempStatus temperature_telcheck(float temp);

Health machine_health_check(TempStatus temp_check, bool running);