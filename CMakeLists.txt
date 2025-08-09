cmake_minimum_required(VERSION 3.16)
project(Ostival)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)

add_executable(Ostival
    src/OstivalMain.cpp
    src/config.cpp
)

target_include_directories(Ostival PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(Ostival PRIVATE Qt6::Widgets)