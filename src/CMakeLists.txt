set(HEADERS
        Book.h
        Limit.h
        Order.h
        Trade.h
        Types.h
)

set(SOURCES
        Book.cpp
        Limit.cpp
        Order.cpp
)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${HEADERS} ${SOURCES})