cmake_minimum_required(VERSION 3.28)
project(OrderBook)

set(CMAKE_CXX_STANDARD 17)

add_executable(OrderBook
    src/main.cpp
    src/Order.cpp
    src/OrderBook.cpp
    src/BookLevel.cpp
    include/Order.h
    include/OrderBook.h
    include/Types.h
    include/Trade.h
    include/BookLevel.h
)