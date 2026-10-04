cmake_minimum_required(VERSION 3.13)

project(machine_logger CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(machine_logger
    src/main.cpp
    src/csv.cpp
    src/tick.cpp
    src/timestamp.cpp
)

target_include_directories(machine_logger PRIVATE
    include
)