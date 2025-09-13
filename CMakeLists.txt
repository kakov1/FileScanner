cmake_minimum_required(VERSION 3.11)
project(Scanner)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(scanner main.cpp)

target_link_libraries(scanner
    PUBLIC
    scanner_lib
    Boost::program_options
)

add_subdirectory(src)
add_subdirectory(tests)
