add_library(i2c_lib
    inc/i2c.h
    src/i2c.c
)

target_include_directories(i2c_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")