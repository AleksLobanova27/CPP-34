cmake_minimum_required(VERSION 3.22.0)
project(ExtArrayTests)

# Настройка Google Test
find_package(GTest REQUIRED)
include(GoogleTest)

# Добавление исполняемого файла с тестами
add_executable(ExtArrayTests
    ExtArray.cpp
    ExtArrayTests.cpp
)

# Google Test
target_link_libraries(ExtArrayTests GTest::GTest GTest::Main)

# Добавление тестов
gtest_discover_tests(ExtArrayTests)