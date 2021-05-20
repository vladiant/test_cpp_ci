cmake_minimum_required(VERSION 3.10)

project(CppProjectSample LANGUAGES CXX)

add_subdirectory(googletest)

# Library
add_library(
    SampleLib
    lib/include/simple_calc.hpp
    lib/include/i_warper.hpp
    lib/include/basic_warper.hpp
    lib/include/checked_warper.hpp
    lib/include/clamped_warper.hpp
    lib/include/operation_strategy.hpp
    lib/src/basic_warper.cpp
    lib/src/checked_warper.cpp
    lib/src/clamped_warper.cpp
    lib/src/operation_strategy.cpp
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
    test/test_checked_warper.cpp
    test/test_clamped_warper.cpp
    test/test_mocked_warper.cpp
    test/test_operation_strategy.cpp
    test/test_operation_strategy_logic.cpp
    test/test_operation_strategy_edge.cpp
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
        gtest_main
        gmock_main
)

add_test(NAME TestSampleLib COMMAND TestSampleLib)
