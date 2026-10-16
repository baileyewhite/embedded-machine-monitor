#include "csv.h"

std::ofstream create_telemetry_csv()
{
    std::ofstream csvFile("./logs/telemetry.csv");

    if (!csvFile.is_open())
    {
        std::cerr << "Error: Couldn't open ./logs/telemetry.csv\n";
        return csvFile;
    }

    csvFile << "timestamp,machine_state,temperature,temp_status,health" << std::endl;

    return csvFile;
}
