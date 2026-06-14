cmake_minimum_required(VERSION 4.0)
project(OOP_Test)

set(CMAKE_CXX_STANDARD 23)

add_executable(OOP_Test main.cpp
        Enums.h
        Review.cpp
        Review.h
        Fragrance.cpp
        Fragrance.h
        Discount.cpp
        Discount.h
        Purchase.cpp
        Purchase.h
        User.cpp
        User.h
        Customer.cpp
        Customer.h
        NotinOOP.cpp
        NotinOOP.h)
