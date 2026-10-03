# Embedded Machine Monitor

A C++ embedded systems project built around a Raspberry Pi Pico W and Raspberry Pi.

The goal of this project is to develop a small machine-monitoring system that reads physical inputs, evaluates machine condition, and reports telemetry to a Raspberry Pi for logging and analysis.

The current version is a prototype. A push button is used to simulate a machine's `RUNNING` / `STOPPED` state, while the Pico W's internal temperature sensor is used to develop and test sensor-processing and health-classification logic.

## Current Features

- Raspberry Pi used as the Linux development and build machine
- Raspberry Pi Pico W firmware written in C++
- Pico SDK and CMake-based build system
- USB serial telemetry from the Pico W to the Raspberry Pi
- Internal RP2040 temperature sensor sampled using the ADC
- Raw ADC readings converted into temperature
- Temperature classified as:
  - `NORMAL`
  - `WARNING`
  - `CRITICAL`
- GPIO push button used to simulate machine `RUNNING` / `STOPPED` state
- Pico W onboard LED reflects the simulated machine state
- Combined machine-health evaluation using machine state and temperature status
- Initialization failure handling for the machine-state input
- Bash script for automated firmware flashing
- Git and GitHub version control

## Example Telemetry

```text
Tick: 42 | Machine(Button): RUNNING | Temp: 16.34 °C | Temp Status: NORMAL | Health: HEALTHY
```

The firmware currently reports telemetry once per second over USB.

## Health Logic

The prototype combines machine state and temperature status to determine an overall machine-health result.

| Machine State | Temperature Status | Overall Health |
| --- | --- | --- |
| `RUNNING` | `NORMAL` | `HEALTHY` |
| `RUNNING` | `WARNING` | `WARNING` |
| `RUNNING` | `CRITICAL` | `FAULT` |
| `STOPPED` | `NORMAL` | `IDLE` |
| `STOPPED` | `WARNING` | `WARNING` |
| `STOPPED` | `CRITICAL` | `INVESTIGATE` |

If the machine-state input cannot be initialized, the overall health is reported as `UNKNOWN`.

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
├── experiments/
│   ├── blink/
│   └── button-led/
├── scripts/
│   └── flash.sh
└── README.md
```

## Firmware Modules

### `main.cpp`

Coordinates sensor readings, machine-state readings, health evaluation, and telemetry output.

### `temp.cpp`

Handles temperature conversion from the RP2040's internal ADC temperature sensor.

### `machine.cpp`

Handles GPIO input, simulated machine `RUNNING` / `STOPPED` state, and control of the Pico W onboard LED.

### `telemetry.cpp`

Classifies temperature readings and combines temperature status with machine state to determine overall machine health.

## Building

The firmware is built on the Raspberry Pi using the Pico SDK and ARM cross-compiler.

### Configure

```bash
cmake -S firmware -B firmware/build -DPICO_BOARD=pico_w
```

### Build

```bash
cmake --build firmware/build -j4
```

The resulting firmware image is generated at:

```text
firmware/build/machine_monitor.uf2
```

## Flashing

The project includes a Bash script that detects a Pico W in BOOTSEL mode, mounts it, and copies the generated UF2 firmware.

After connecting the Pico W in BOOTSEL mode:

```bash
./scripts/flash.sh
```

## Current Prototype Hardware

- Raspberry Pi Pico W
- Raspberry Pi
- Momentary push button
- 1 kΩ resistor
- Breadboard
- Jumper wires

The push button currently acts as a simulated machine-state signal.

## Planned Development

Future versions of the project are intended to replace the simulated inputs with measurements from a real small machine, such as a 5 V fan.

Planned additions include:

- External temperature sensing
- Fan or motor speed measurement
- Additional machine-health signals such as current draw or vibration
- Raspberry Pi telemetry logging
- Historical data analysis
- More robust machine fault detection
- Improved telemetry protocol
- Possible dashboard or alerting system

## Project Goals

This project is being developed to build practical experience with:

- Embedded C and C++
- Microcontroller peripherals
- GPIO
- ADCs
- Sensor interfacing
- Firmware architecture
- CMake
- Linux development tools
- Serial communication
- Hardware/software integration
- Machine-condition monitoring