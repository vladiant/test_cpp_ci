cmake_minimum_required(VERSION 3.10)

project(CppProjectSample LANGUAGES CXX)

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
#    test/test_mocked_warper.cpp
#    test/test_operation_strategy.cpp
#    test/test_operation_strategy_logic.cpp
#    test/test_operation_strategy_edge.cpp
    test/main.cpp
)

set_target_properties(
    TestSampleLib
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

# Fix for the Windows build
target_compile_definitions(
    TestSampleLib
    PRIVATE
    -DNOMINMAX
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


# To be used with memcheck.yml
find_program(VALGRIND valgrind)
if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=40 --track-origins=yes --track-fds=yes --log-file=memcheck.txt $<TARGET_FILE:TestSampleLib>)
else()
    add_custom_target(valgrind COMMENT "Valgrind not found")
endif()


# Package generation
install(
    TARGETS
       SampleLib
       SampleLibApp
       TestSampleLib
    DESTINATION 
       sample_lib
)

set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION "Minimal C++ test example")
set(CPACK_GENERATOR "DEB") # Debian package
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON) # autogenerate dependency information
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Code Author") # mandatory

include(CPack)
