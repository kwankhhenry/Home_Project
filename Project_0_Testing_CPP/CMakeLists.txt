cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        )

#add_executable(main src/main.cpp)
add_executable(${PROJECT_NAME}
                ${all_SRCS})

# Include + Linking directories
target_include_directories(${PROJECT_NAME} PRIVATE 
                ${PROJECT_SOURCE_DIR}/src)
target_link_directories(${PROJECT_NAME} PRIVATE /home/admin/External_lib/googletest/build/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

# Enable test modules
enable_testing()
add_subdirectory(tests)