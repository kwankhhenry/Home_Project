cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        )

add_executable(${PROJECT_NAME}
        ${all_SRCS})