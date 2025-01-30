# Manual run options upon Configuation
# cmake -B build
#       -G "Ninja"
#       -DLIB_TYPE=SHARED (Custom Library Type = SHARED (Default), STATIC, INTERFACE)
#       -DCMAKE_BUILD_TYPE=Debug or (-DCMAKE_CONFIGURATION_TYPES="Debug;Release" for multi-config)
#       -DCMAKE_INSTALL_PREFIX=/home/admin/Home_Project/Internal_lib 

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

# Include here not to confused with actual project include directories
include_directories(${IcecreamCpp_INCLUDE_DIRS})

# Actual Project files and executables
file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        )

add_executable(${PROJECT_NAME}
                ${all_SRCS})

# Include + Linking directories when building the project
target_include_directories(${PROJECT_NAME} PRIVATE )
target_link_directories(${PROJECT_NAME} PRIVATE )
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)


# Build and Install headers and libraries (cmake --build . --install . --prefix /home/admin/Home_Project/Internal_lib)
# https://youtu.be/08f5Dav72aE?si=4PNqxkcoKyqCQC5T
# https://dominikberner.ch/cmake-interface-lib/
set(LIB_NAME ThreadPool)
set(INTERNAL_LIB_DIR /home/admin/Home_Project/Internal_lib)

# Single option for library type: SHARED (Default), STATIC, or INTERFACE
set(LIB_TYPE "SHARED" CACHE STRING "Choose library type: SHARED (Default), STATIC, INTERFACE")
set_property(CACHE LIB_TYPE PROPERTY STRINGS "SHARED" "STATIC" "INTERFACE")

# Create the library based on LIB_TYPE
if (LIB_TYPE STREQUAL "SHARED")
    add_library(${LIB_NAME} SHARED ${all_SRCS})
    set_target_properties(${LIB_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON) # Set library properties (only for shared library)
    message(STATUS "Building ${LIB_NAME} as SHARED library")
elseif (LIB_TYPE STREQUAL "STATIC")
    add_library(${LIB_NAME} STATIC ${all_SRCS})
    message(STATUS "Building ${LIB_NAME} as STATIC library")
elseif (LIB_TYPE STREQUAL "INTERFACE")
    add_library(${LIB_NAME} INTERFACE)

    # Set include directories for build and install scenarios for INTERFACE libraries - when another project links to this library
    target_compile_features(${LIB_NAME} INTERFACE cxx_std_20)
    target_include_directories(${LIB_NAME} INTERFACE 
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)  # Include directories for build and install scenarios
    message(STATUS "Building ${LIB_NAME} as INTERFACE library")
else()
    message(FATAL_ERROR "Must select a library type (SHARED, STATIC, INTERFACE)")
endif()

# BEGIN install library 
include(GNUInstallDirs)  # Standard install directories

# Set a custom install directory. Add "CACHE PATH "Custom install directory" FORCE" to set it as default
# If not defined then default install location is /usr/local
set(CMAKE_INSTALL_PREFIX "${INTERNAL_LIB_DIR}")

# Set path configs to be EXPORT as Target .cmake file and used by package manager to determine paths
install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets  # Export ${LIB_NAME}Targets to be used to generate CMake config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
)

# Install headers from source DIRECTORY (at src/) to designated DESTINATION location
install(DIRECTORY src/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h")

# Export the package configuration for find_package()
# Generate CMake target files with above EXPORT details
install(EXPORT ${LIB_NAME}Targets 
    #FILE ${LIB_NAME}Targets.cmake            # Specify the file name otherwise it will be ${LIB_NAME}Targets.cmake
    DESTINATION lib/cmake/${LIB_NAME}
    NAMESPACE MyLib::
    CONFIGURATIONS Release Debug             # Tells CMake not to generate -noconfig.cmake files, but expects Release & Debug
)

# Use configure_package_config_file() to enable relocatable installs
#list(APPEND CMAKE_PREFIX_PATH /home/admin/Home_Project/Internal_lib/lib/cmake)
#find_package(ThreadPool CONFIG REQUIRED)

# Generate config files required to find library package
# https://www.f-ax.de/dev/2020/10/07/cmake-config-package.html
include(CMakePackageConfigHelpers)

# 📌 Step 1: Auto-generate ${LIB_NAME}Config.cmake.in
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake.in "
@PACKAGE_INIT@

include(\"\${CMAKE_CURRENT_LIST_DIR}/${LIB_NAME}Targets.cmake\")

check_required_components(${LIB_NAME})
")

# 📌 Step 2: Use configure_package_config_file() for relocatable installation
configure_package_config_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake.in      # Config file template
    ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake         # CMake config files that points to the Target files (File generated above)
   INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME}
)

# 📌 Step 3: Install rules for relocatable package
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME}
)

# Enable test modules
enable_testing()
add_subdirectory(tests)