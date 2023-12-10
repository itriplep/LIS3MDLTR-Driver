#ifndef I2C_H
#define I2C_H

#include <stdint.h>

// i2c functions
void i2c_read(uint8_t bus_address, uint8_t register_address, uint8_t *buffer,
              uint16_t length);
void i2c_write(uint8_t bus_address, uint8_t register_address, uint8_t *data,
               uint16_t length);

#endif // I2C_H