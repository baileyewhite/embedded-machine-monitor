# Embedded Machine Monitor

A C++ embedded systems project built around a Raspberry Pi Pico W and Raspberry Pi.

The project is a prototype condition-monitoring system. The Pico W reads physical inputs, classifies machine state and temperature condition, and sends structured telemetry over USB serial. A C++ logger running on the Raspberry Pi receives that telemetry, validates and parses it into typed data, adds timestamps, and stores the results in CSV format.

The current hardware is intentionally simple: a push button simulates a machine's `RUNNING` / `STOPPED` state, while the Pico W's internal temperature sensor is used to develop the sensing, telemetry, parsing, and machine-health pipeline before moving to an external machine and sensors.

## System Architecture

```text
Physical Input / Pico Temperature Sensor
                  |
                  v
        Raspberry Pi Pico W
        --------------------
        GPIO + ADC sampling
        Typed machine state
        Temperature status
        Health classification
                  |
                  | USB serial
                  v
           Raspberry Pi
        --------------------
        C++ serial logger
        Telemetry parsing
        Validation
        Timestamping
        CSV persistence
```

The firmware and logger share the same telemetry enum definitions and string-conversion code so both programs use a consistent data model.

## Current Features

### Pico W Firmware

- Firmware written in C++ using the Raspberry Pi Pico SDK
- CMake-based cross-compilation for the Pico W
- Internal RP2040 temperature sensor sampled through the ADC
- ADC voltage converted to temperature in Celsius
- GPIO push button used to simulate machine `RUNNING` / `STOPPED` state
- Pico W onboard LED reflects the simulated machine state
- Temperature classified as `NORMAL`, `WARNING`, or `CRITICAL`
- Combined machine-health classification including `HEALTHY`, `IDLE`, `WARNING`, `FAULT`, `INVESTIGATE`, fallback, and unknown states
- Strongly typed `enum class` values used internally for machine state, temperature status, and health
- Enum values converted to text only at the serial communication boundary
- USB serial telemetry transmitted once per second
- Bash flashing script for copying the generated UF2 firmware to a Pico in BOOTSEL mode

### Raspberry Pi Logger

- C++17 Linux application
- Reads telemetry from `/dev/ttyACM0`
- Ignores empty serial records
- Parses comma-separated telemetry into a typed `Tick` structure
- Uses `std::optional` to reject malformed telemetry
- Validates telemetry enum fields through shared string-to-enum conversion functions
- Handles invalid and out-of-range numeric conversions
- Adds local timestamps to valid telemetry records
- Prints valid telemetry to the terminal
- Writes timestamped telemetry to `logs/telemetry.csv`

### Shared Telemetry Model

The firmware and logger both compile the same shared telemetry code:

```text
shared/
├── include/
│   └── telemetry_enums.h
└── src/
    └── telemetry_enums.cpp
```

The shared model defines `MachineState`, `TempStatus`, and `Health`, along with enum-to-string and string-to-enum conversion functions. This keeps the serial protocol consistent between the embedded firmware and Linux logger and avoids maintaining duplicate telemetry definitions.

## Telemetry Format

The Pico currently sends one comma-separated telemetry record per second:

```text
STOPPED,14.02,NORMAL,IDLE
RUNNING,15.43,NORMAL,HEALTHY
```

The fields are:

```text
machine_state,temperature,temp_status,health
```

The Raspberry Pi logger adds a timestamp before writing the record:

```text
2026-10-16 12:11:51,STOPPED,14.02,NORMAL,IDLE
2026-10-16 12:11:56,RUNNING,15.43,NORMAL,HEALTHY
```

The CSV header is:

```text
timestamp,machine_state,temperature,temp_status,health
```

## Health Logic

The current prototype combines the simulated machine state with the temperature classification.

| Machine State | Temperature Status | Overall Health |
| --- | --- | --- |
| `RUNNING` | `NORMAL` | `HEALTHY` |
| `RUNNING` | `WARNING` | `WARNING` |
| `RUNNING` | `CRITICAL` | `FAULT` |
| `STOPPED` | `NORMAL` | `IDLE` |
| `STOPPED` | `WARNING` | `WARNING` |
| `STOPPED` | `CRITICAL` | `INVESTIGATE` |

If the machine-state input cannot be initialized, the firmware reports the machine state as `N/A` and health as `UNKNOWN`.

## Project Structure

```text
embedded-machine-monitor/
├── firmware/
│   ├── include/
│   │   ├── machine.h
│   │   ├── telemetry.h
│   │   └── temp.h
│   ├── src/
│   │   ├── machine.cpp
│   │   ├── main.cpp
│   │   ├── telemetry.cpp
│   │   └── temp.cpp
│   └── CMakeLists.txt
├── logger/
│   ├── include/
│   │   ├── csv.h
│   │   ├── tick.h
│   │   └── timestamp.h
│   ├── src/
│   │   ├── csv.cpp
│   │   ├── main.cpp
│   │   ├── tick.cpp
│   │   └── timestamp.cpp
│   └── CMakeLists.txt
├── shared/
│   ├── include/
│   │   └── telemetry_enums.h
│   └── src/
│       └── telemetry_enums.cpp
├── logs/
│   └── telemetry.csv
├── scripts/
│   └── flash.sh
├── experiments/
│   ├── blink/
│   └── button-led/
├── .gitignore
└── README.md
```

## Firmware Modules

### `firmware/src/main.cpp`

Coordinates ADC sampling, machine-state input, temperature classification, health evaluation, LED behavior, and telemetry serialization.

### `firmware/src/temp.cpp`

Converts the RP2040 internal temperature-sensor ADC voltage into a Celsius temperature value.

### `firmware/src/machine.cpp`

Initializes and reads the GPIO push button, controls the Pico W onboard LED, and converts the button state into a `MachineState`.

### `firmware/src/telemetry.cpp`

Converts temperature readings into `TempStatus` values and combines temperature condition with machine state to determine a `Health` value.

## Logger Modules

### `logger/src/main.cpp`

Opens the Pico USB serial device, receives telemetry lines, invokes the parser, generates timestamps, prints valid records, and writes them to CSV.

### `logger/src/tick.cpp`

Parses incoming serial records into a typed `Tick` structure. The parser validates field count, telemetry enum values, and numeric conversion before returning either a valid `Tick` or `std::nullopt`.

### `logger/src/timestamp.cpp`

Generates local timestamps for telemetry records.

### `logger/src/csv.cpp`

Creates the telemetry CSV file and writes the CSV header.

## Building the Firmware

The firmware is built on the Raspberry Pi using the Pico SDK and ARM cross-compiler.

Configure the firmware build:

```bash
cmake -S firmware -B firmware/build -DPICO_BOARD=pico_w
```

Build:

```bash
cmake --build firmware/build -j4
```

The generated UF2 file is:

```text
firmware/build/machine_monitor.uf2
```

## Flashing the Pico W

Put the Pico W into BOOTSEL mode, connect it to the Raspberry Pi, and run:

```bash
./scripts/flash.sh
```

The flashing script detects the Pico storage device, mounts it, and copies the generated UF2 firmware.

## Building the Raspberry Pi Logger

Configure the logger:

```bash
cmake -S logger -B logger/build
```

Build:

```bash
cmake --build logger/build -j4
```

Run from the repository root:

```bash
./logger/build/machine_logger
```

The logger currently expects the Pico W USB serial device at:

```text
/dev/ttyACM0
```

Valid telemetry is printed to the terminal and written to:

```text
logs/telemetry.csv
```

## Current Prototype Hardware

- Raspberry Pi Pico W
- Raspberry Pi
- Momentary push button
- 1 kΩ resistor
- Breadboard
- Jumper wires
- USB connection between the Raspberry Pi and Pico W

The push button currently represents whether the simulated machine is running. The Pico W's internal temperature sensor is being used as a development signal rather than as a final machine-temperature sensor.

## Development Approach

The project is being developed incrementally. The current prototype was built first to establish the complete software and communication pipeline before introducing additional machine hardware:

```text
physical input
    ->
Pico firmware
    ->
typed telemetry
    ->
USB serial protocol
    ->
Raspberry Pi parser
    ->
timestamped CSV logging
```

Future hardware can therefore replace the prototype input sources without requiring the entire telemetry and logging architecture to be redesigned.

## Planned Development

The next major stage is to replace simulated inputs with measurements from a real low-voltage machine, such as a small brushless fan.

Potential future additions include:

- External temperature sensing
- Fan or motor RPM measurement
- Replacing the push button with measured machine state
- Current-draw sensing
- Vibration sensing
- Multi-signal machine-health classification
- Serial disconnect and reconnect handling
- Automated parser tests
- Improved log/session management
- Historical telemetry analysis
- Optional dashboard or alerting features

The goal is to move from simple sensor reporting toward condition monitoring, where multiple physical measurements can be combined to identify abnormal machine behavior.

## Project Goals

This project is intended to build practical experience with:

- Embedded C++
- Raspberry Pi Pico SDK
- Microcontroller GPIO and ADC peripherals
- Sensor interfacing
- Firmware architecture
- Cross-compilation
- CMake
- Linux C++ development
- USB serial communication
- Data serialization and parsing
- Strongly typed enums
- `std::optional`
- Exception-aware parsing
- Shared code across embedded and Linux targets
- CSV data logging
- Hardware/software integration
- Machine-condition monitoring
- Git and GitHub workflows
