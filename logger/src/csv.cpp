#include "csv.h"

std::ofstream create_telemetry_csv()
{
    std::ofstream csvFile("./logs/telemetry.csv");

    if (!csvFile.is_open())
        printf("Couldn't open 'telemetry.csv' file");
    
    csvFile << "timestamp,machine_state,temperature,temp_status,health" << std::endl;

    return csvFile;
}
