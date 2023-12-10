cmake_minimum_required(VERSION 3.22.1)

#Project
project(LIS3MDLTR)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(hal)
add_subdirectory(platform)

add_executable(exe src/main.c)

#include directory for exe target
target_include_directories(exe PRIVATE
    ${CMAKE_SOURCE_DIR}/hal #include hal directory
    ${CMAKE_SOURCE_DIR}/platform #include platform directory
)

target_link_libraries(exe PRIVATE i2c_lib)
target_link_libraries(exe PRIVATE lis3mdltr_lib)


