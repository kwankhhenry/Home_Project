cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)
#include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/Timer)

file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        )

add_executable(${PROJECT_NAME}
                ${all_SRCS})

target_link_libraries(main PRIVATE timer)
#install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/build/)
