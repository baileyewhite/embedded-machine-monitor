cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(machine_monitor C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(machine_monitor
    src/main.cpp
    src/temp.cpp
    src/telemetry.cpp
)

target_link_libraries(machine_monitor
    pico_stdlib
    hardware_adc
)

target_include_directories(machine_monitor PRIVATE
    include
)

pico_enable_stdio_usb(machine_monitor 1)
pico_enable_stdio_uart(machine_monitor 0)

pico_add_extra_outputs(machine_monitor)