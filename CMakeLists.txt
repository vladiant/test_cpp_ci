cmake_minimum_required(VERSION 3.10)

project(CppProjectSample LANGUAGES CXX)

# Library
add_library(
    SampleLib
    lib/include/simple_calc.hpp
    lib/include/basic_warper.hpp
    lib/src/basic_warper.cpp
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

# Test of Library
include(CTest)

add_executable(
    TestSampleLib
    test/test_simple_calc.cpp
    test/test_basic_warper.cpp
    test/main.cpp
)

set_target_properties(
    TestSampleLib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_include_directories(
    TestSampleLib
    PRIVATE
        .
)

target_link_libraries(
    TestSampleLib
    PRIVATE
        SampleLib
)

add_test(NAME TestSampleLib COMMAND TestSampleLib)
