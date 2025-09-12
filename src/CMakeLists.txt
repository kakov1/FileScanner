add_library(scanner_lib scanner.cpp queue.cpp thread_pool.cpp details.cpp)

target_include_directories(scanner_lib PUBLIC ${CMAKE_SOURCE_DIR}/inc)

target_link_libraries(scanner_lib PUBLIC OpenSSL::Crypto)