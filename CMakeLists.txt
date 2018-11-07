cmake_minimum_required(VERSION 3.12)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Assignment1
        include/Action.h
        include/Customer.h
        include/Dish.h
        include/Restaurant.h
        include/Table.h
        src/Action.cpp
        src/Customer.cpp
        src/Dish.cpp
        src/Main.cpp
        src/Restaurant.cpp
        src/Table.cpp)
