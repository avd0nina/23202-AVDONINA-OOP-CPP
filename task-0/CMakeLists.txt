cmake_minimum_required(VERSION 3.29)
project(23202_AVDONINA_OOP_CPP)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(23202_AVDONINA_OOP_CPP
        task-0/src/main.cpp
        task-0/src/FileReader.h
        task-0/src/FileReader.cpp
        task-0/src/Parser.h
        task-0/src/Parser.cpp
        task-0/src/Statistic.h
        task-0/src/Statistic.cpp
        task-0/src/Printer.h
        task-0/src/Printer.cpp
)

add_executable(FileReaderTest task-0/src/FileReaderTest.cpp task-0/src/FileReader.cpp)
add_executable(ParserTest task-0/src/ParserTest.cpp task-0/src/Parser.cpp)
add_executable(StatisticTest task-0/src/StatisticTest.cpp task-0/src/Statistic.cpp)

target_link_libraries(FileReaderTest GTest::gtest_main)
target_link_libraries(ParserTest GTest::gtest_main)
target_link_libraries(StatisticTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(FileReaderTest)
gtest_discover_tests(ParserTest)
gtest_discover_tests(StatisticTest)

enable_testing()
