cmake_minimum_required(VERSION 3.16.3)
project(main VERSION 1.0.0)

set(BOOST_LIB_DIR /home/admin/External_lib/boost_lib)

file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        )

add_executable(${PROJECT_NAME}
        ${all_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${BOOST_LIB_DIR}/include)
#target_link_directories(${PROJECT_NAME} PRIVATE ${BOOST_LIB_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)