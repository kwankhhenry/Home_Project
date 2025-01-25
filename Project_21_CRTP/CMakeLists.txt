cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")  # valgrind configurations
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -pg -no-pie -fno-builtin")  # gprof configurations
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(EXTERNAL_LIB /home/admin/External_lib)

add_executable(main src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_LIB}/include)
target_link_libraries(${PROJECT_NAME} pthread)