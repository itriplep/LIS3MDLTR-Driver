include_directories(${CMAKE_SOURCE_DIR}/hal/inc)

add_library(lis3mdltr_lib
    inc/LIS3MDLTR.h
    src/LIS3MDLTR.c
)

target_include_directories(lis3mdltr_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")