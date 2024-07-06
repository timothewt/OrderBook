cmake_minimum_required(VERSION 3.28)
project(OrderBook)

set(CMAKE_CXX_STANDARD 20)
add_executable(${CMAKE_PROJECT_NAME}_run main.cpp)

include_directories(src)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(demo)

target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib demo_lib)