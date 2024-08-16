cmake_minimum_required(VERSION 3.16.3)
project(timer VERSION 1.0.0)

list(APPEND
        CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_library(
    ${PROJECT_NAME} SHARED
    ${PROJECT_SOURCE_DIR}/src/Timer.cpp
    ${PROJECT_SOURCE_DIR}/src/Timer.h
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
export(TARGETS timer FILE myTimerTargets.cmake)