cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_executable(main src/main.cpp)
target_link_libraries(${PROJECT_NAME} pthread)