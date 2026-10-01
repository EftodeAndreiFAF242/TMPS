cmake_minimum_required(VERSION 3.20)

project(CivicDesk
    VERSION 0.1.0
    DESCRIPTION "Civic issue reporting backend - TMPS laboratory project"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CIVICDESK_BUILD_TESTS "Build the unit tests" ON)
option(CIVICDESK_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# Single-config generators (Ninja, Makefiles) build without optimisation unless told otherwise.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Link the MinGW runtime statically, so the programs start without its DLLs on PATH.
if(MINGW)
    add_link_options(-static)
endif()

# The warning flags every target of the project is compiled with.
add_library(civicdesk_warnings INTERFACE)
if(MSVC)
    target_compile_options(civicdesk_warnings INTERFACE
        /W4 /permissive- /utf-8
        $<$<BOOL:${CIVICDESK_WARNINGS_AS_ERRORS}>:/WX>)
else()
    target_compile_options(civicdesk_warnings INTERFACE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wnon-virtual-dtor
        $<$<BOOL:${CIVICDESK_WARNINGS_AS_ERRORS}>:-Werror>)
endif()

# Everything except main() lives in a library, so the tests link the same code the program runs.
add_library(civicdesk_core STATIC
    src/domain/GeoPoint.cpp
    src/domain/Report.cpp
    src/domain/DeadlineCalculator.cpp
    src/validation/ReportValidator.cpp
    src/validation/rules/ServiceAreaRule.cpp
    src/validation/rules/DescriptionLengthRule.cpp
    src/validation/rules/DescriptionRequiredRule.cpp
    src/specification/Specifications.cpp
    src/application/ReportService.cpp
    src/infrastructure/InMemoryReportRepository.cpp
    src/infrastructure/ConsoleNotifier.cpp
    src/infrastructure/SequentialIdGenerator.cpp
    src/presentation/ReportFormatter.cpp)
target_include_directories(civicdesk_core PUBLIC src)
target_link_libraries(civicdesk_core PRIVATE civicdesk_warnings)

add_executable(civicdesk app/main.cpp)
target_link_libraries(civicdesk PRIVATE civicdesk_core civicdesk_warnings)

if(CIVICDESK_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
