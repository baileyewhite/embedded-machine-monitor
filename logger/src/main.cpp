#include <iostream>

#include "csv.h"
#include "tick.h"
#include "timestamp.h"

int main()
{
    std::ifstream serial("/dev/ttyACM0");

    if(!serial.is_open())
    {
        std::cerr << "Error: Couldn't open /dev/ttyACM0\n";
        return 1;
    }

    std::string line;

    std::string timestamp;

    std::ofstream csvFile = create_telemetry_csv();
    if (!csvFile.is_open())
        return 1;

    while(std::getline(serial, line))
    {
        if(line.empty())
            continue;

        timestamp = get_timestamp();

        std::optional<Tick> tick = parse_telemetry_tick(line);

        if(!tick)
            std::cerr << "Error: Invalid Tick Object\n";

        else
        {
            std::cout << timestamp << ',' << *tick << '\n';
            csvFile << timestamp << ',' << *tick << std::endl;
        }
    }

    return 0;
}