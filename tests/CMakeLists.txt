enable_testing()

add_executable(test_util test.cpp)

target_link_libraries(test_util PUBLIC scanner_lib GTest::gtest)

target_compile_definitions(test_util PUBLIC TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

include(GoogleTest)
gtest_discover_tests(test_util)
