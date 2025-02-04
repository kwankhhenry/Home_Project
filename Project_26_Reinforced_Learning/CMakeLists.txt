# CMake Basic Parameters
cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")  # valgrind configurations
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -pg -no-pie -fno-builtin")  # gprof configurations
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Useful alias
set(EXTERNAL_LIB_DIR /home/admin/External_lib)

# Note: redfine e.g.
#       -DCMAKE_INSTALL_PREFIX=/home/admin/External_lib 
#       -DCMAKE_INSTALL_LIBDIR=/home/admin/External_lib/lib 
#       -DCMAKE_INSTALL_INCLUDEDIR=/home/admin/External_lib/include
# if you wanna custom install file locations
# Find icecream package (Config Mode)
list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_LIB_DIR}/lib/cmake)
find_package(IcecreamCpp CONFIG REQUIRED)

list(APPEND CMAKE_PREFIX_PATH /home/admin/Home_Project/Internal_lib/lib/cmake)
find_package(ThreadPool CONFIG REQUIRED)

# Include here not to confused with actual project include directories
include_directories(${IcecreamCpp_INCLUDE_DIRS})

# Actual Project files and executables
file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        )

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