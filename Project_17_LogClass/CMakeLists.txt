cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        )

add_executable(${PROJECT_NAME}
        ${all_SRCS})

#target_include_directories(${PROJECT_NAME} PRIVATE ${BOOST_LIB_DIR}/include)
#target_link_directories(${PROJECT_NAME} PRIVATE ${BOOST_LIB_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

# Exporting headers and libraries
# https://youtu.be/08f5Dav72aE?si=4PNqxkcoKyqCQC5T
# https://dominikberner.ch/cmake-interface-lib/
set(LIB_NAME Logging)
set(HOME_PROJECT_DIR /home/admin/Home_Project)
set(INTERNAL_LIB_DIR ${HOME_PROJECT_DIR}/Internal_lib)

# Set up library target
add_library(${LIB_NAME} INTERFACE)

# BEGIN install library 
include(GNUInstallDirs)
target_compile_features(${LIB_NAME} INTERFACE cxx_std_17)

# Set include directories for build and install scenarios - when used by external sources
target_include_directories(${LIB_NAME}
        INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Install header to designated location
install(FILES src/Logging.h DESTINATION ${INTERNAL_LIB_DIR}/include)

# Set path configs to be EXPORT as target .cmake file and used by package manager to determine paths
install(TARGETS ${LIB_NAME} 
    EXPORT ${LIB_NAME}Targets  # Export ${LIB_NAME}_Targets to be used to generate CMake config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} #${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${INTERNAL_LIB_DIR}/lib #${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} #${INTERNAL_LIB_DIR}/bin
    INCLUDES DESTINATION ${INTERNAL_LIB_DIR}/include #${CMAKE_INSTALL_INCLUDEDIR}
)

# Generate CMake target files with above EXPORT 
install(EXPORT ${LIB_NAME}Targets
        FILE ${LIB_NAME}Targets.cmake  # CMake Target files details (lib path, include path, bin path, etc.)
        DESTINATION ${INTERNAL_LIB_DIR}/lib/cmake/${LIB_NAME}
        NAMESPACE MyLib::
)

# Generate config files required to find library package
# https://www.f-ax.de/dev/2020/10/07/cmake-config-package.html
include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake  # CMake config files that points to the Target files (File generated above)
        INSTALL_DESTINATION ${INTERNAL_LIB_DIR}/lib/cmake/${LIB_NAME}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}Config.cmake
        DESTINATION ${INTERNAL_LIB_DIR}/lib/cmake/${LIB_NAME}
)