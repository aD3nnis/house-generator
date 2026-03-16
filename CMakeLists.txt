cmake_minimum_required(VERSION 3.16)
project(house_generator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(house_generator
    src/main.cpp
    src/systems/LayoutGenerator.cpp
    src/systems/LayoutOutput.cpp
    src/systems/RuleValidator.cpp
)

target_include_directories(house_generator PRIVATE include)
