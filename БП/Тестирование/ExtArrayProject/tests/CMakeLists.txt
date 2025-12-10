find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(ExtArrayTests
    ExtArrayTests.cpp
    ${PROJECT_SOURCE_DIR}/src/ExtArray.cpp
)

target_include_directories(ExtArrayTests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(ExtArrayTests
    GTest::GTest
    GTest::Main
)

gtest_discover_tests(ExtArrayTests)