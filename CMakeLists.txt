cmake_minimum_required(VERSION 3.20)

project(calculus)

add_library(calculus
    calculus.hpp
    calculus.cpp)

set_target_properties(calculus PROPERTIES CXX_STANDARD 23)
target_include_directories(calculus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_calculus
    main.cpp)

set_target_properties(test_calculus PROPERTIES CXX_STANDARD 23)
target_link_libraries(test_calculus PUBLIC calculus)
