cmake_minimum_required(VERSION 3.16)

project(CityReports LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Every .cpp file in the lab folders is part of the program, so a new class needs no change here.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Lab1/*.cpp Lab2/*.cpp Lab3/*.cpp)

add_executable(tmps main.cpp ${SOURCES})

# Include paths start at the project folder, for example #include "Lab1/reports/Report.h".
target_include_directories(tmps PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tmps PRIVATE -Wall -Wextra)
endif()

# The unit tests of laboratory work 3: a separate program, built from the same classes without main.cpp.
add_executable(lab3_tests tests/Lab3Tests.cpp ${SOURCES})
target_include_directories(lab3_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_test(NAME lab3_tests COMMAND lab3_tests)
