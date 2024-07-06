add_library(demo_lib demo.cpp)

target_link_libraries(demo_lib ${CMAKE_PROJECT_NAME}_lib)