#include <iostream>

#include "csv.h"
#include "tick.h"
#include "timestamp.h"

int main()
{
    std::ifstream serial("/dev/ttyACM0");

    if(!serial.is_open())
        printf("Error: Couldn't open '/dev/ttyACM0");
    
    std::string line;

    std::string timestamp;

    std::ofstream csvFile = create_telemetry_csv();

    while(std::getline(serial, line))
    {
        if(line.empty())
            continue;

        timestamp = get_timestamp();

        Tick tick = parse_telemetry_tick(line);

        std::cout << timestamp << ',' << tick << '\n';
        csvFile << timestamp << ',' << tick << std::endl;
    }

    return 0;
}