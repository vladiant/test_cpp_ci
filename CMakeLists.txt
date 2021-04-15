cmake_minimum_required(VERSION 3.10)

project(CppProjectSample LANGUAGES CXX)

# Library
add_library(
    SampleLib
    lib/include/simple_calc.hpp
)

set_target_properties(
    SampleLib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        LINKER_LANGUAGE CXX
        SOVERSION 1
        VERSION 1.0.0
)

target_include_directories(
    SampleLib
    PUBLIC
        lib/include
)

# Sample App
add_executable(
    SampleLibApp
    app/main.cpp
)

set_target_properties(
    SampleLibApp
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_link_libraries(
    SampleLibApp
    PRIVATE
        SampleLib
)
