cmake_minimum_required(VERSION 3.23)
project(DSP-Cpp-filters)
set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        .
        )
