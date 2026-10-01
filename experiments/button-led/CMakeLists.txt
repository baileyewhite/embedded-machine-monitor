cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(button_led C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(button_led
    main.cpp
)

target_link_libraries(button_led
    pico_stdlib
    pico_cyw43_arch_none
)

pico_add_extra_outputs(button_led)
