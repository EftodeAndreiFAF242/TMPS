cmake_minimum_required(VERSION 3.16)

project(CityReports LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Every .cpp file in Lab1/ and Lab2/ is part of the program, so a new class needs no change here.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Lab1/*.cpp Lab2/*.cpp)

add_executable(tmps main.cpp ${SOURCES})

# Include paths start at the project folder, for example #include "Lab1/reports/Report.h".
target_include_directories(tmps PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tmps PRIVATE -Wall -Wextra)
endif()
