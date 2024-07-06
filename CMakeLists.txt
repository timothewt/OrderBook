cmake_minimum_required(VERSION 3.28)
project(OrderBook)

set(CMAKE_CXX_STANDARD 20)

add_executable(OrderBook
        src/main.cpp
        src/Order.cpp
        src/Book.cpp
        include/Order.h
        include/Book.h
        src/Limit.cpp
        include/Limit.h
        include/Types.h
        include/Trade.h
)