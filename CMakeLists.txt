cmake_minimum_required(VERSION 3.28)
project(ooplr6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

file(GLOB LIB_SOURCES "${LIB_DIR}/*.cpp")
add_library(ooplr6_lib ${LIB_SOURCES})
target_include_directories(ooplr6_lib PUBLIC ${INCLUDE_DIR})

add_executable(ooplr6_exe "${SRC_DIR}/main.cpp")
target_link_libraries(ooplr6_exe ooplr6_lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/0953a17a4281fc26831da647ad3fcd5e21e6473b.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB TEST_SOURCES "${TEST_DIR}/*.cpp")
add_executable(ooplr6_tests ${TEST_SOURCES})
target_link_libraries(ooplr6_tests
        ooplr6_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ooplr6_tests)


