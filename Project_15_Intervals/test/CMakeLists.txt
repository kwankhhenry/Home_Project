cmake_minimum_required(VERSION 3.16.3)
project(test VERSION 1.0.0)

#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${source_dir}/include)
#include_directories(${GTEST_INCLUDE_DIR})

#find_package(GTest CONFIG REQUIRED)
#add_subdirectory(/home/admin/Home_Project/external_lib/googletest)
#include(/home/admin/External_lib/googletest/build/googletest/CTestTestfile.cmake)
#include(/home/admin/Home_Project/external_lib/googletest/build/CTestTestfile.cmake)
#include(/home/admin/Home_Project/external_lib/googletest/build/googletest/generated/GTestConfig.cmake)

set(PROJECT_INTERVAL_SOURCE_DIR /home/admin/Home_Project/Project_15_Intervals)

file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_INTERVAL_SOURCE_DIR}/src/interval*.cpp
        ${PROJECT_INTERVAL_SOURCE_DIR}/src/interval*.h
        )

add_executable(${PROJECT_NAME}
                ${all_SRCS})

target_include_directories(test PRIVATE ${PROJECT_INTERVAL_SOURCE_DIR}/src/ /home/admin/External_lib/googletest/googletest/include)
target_link_directories(test PRIVATE /home/admin/External_lib/googletest/build/lib)
target_link_libraries(test PRIVATE gtest gtest_main pthread)
#install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/build/)
