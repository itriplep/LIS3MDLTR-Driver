// -------------------------------------------------------------------------------------------------------
/// \file LIS3MDLTR
/// \brief File description
// -------------------------------------------------------------------------------------------------------
// Implemetation of LIS3MDLTR
// Digital output magnetic sensor (ultralow-power, high-performance 3-axis magnetometer)
// -------------------------------------------------------------------------------------------------------
/// \author: Parvin Parsa
/// \date : 10.Dec.2023
/// Github : itriplep
//  This Driver implemented below purposes
//      a.Retrieve the device’s full-scale configuration
//      b.Retrieve and set the device’s output data rate
//      c.Enable or disable the device’s interrupt pin
//      d.Read the output data of a specific axis
// -------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------
// Include files
//--------------------------------------------------------------------------------------------------------
// Compiler Includes
// All include files that are provided by the compiler directly
#include <stdint.h>                     //!< include to use integer types 
#include <stdbool.h>                    //!< include to use standard boolean
#include <stdio.h>                      //!< include to ise standard io stream for c

//Project Includes
//All include files that are provided by the project
#include "LIS3MDLTR.h"
#include "i2c.h"

//--------------------------------------------------------------------------------------------------------
// Constant and macro definitions
//--------------------------------------------------------------------------------------------------------

#define       CTRL_REG_1         ((uint8_t)0x20)      //!< Address of CTRL REG 1 Register for data rate
#define       CTRL_REG_2         ((uint8_t)0x21)      //!< Address of CTRL REG 2 Register for full-scale
#define       INT_CFG            ((uint8_t)0x30)      //!< Addredd of INT CFG Register for interupt-configuration
#define       FAST_ODR_POS       ((uint8_t)0x01)      //!< FAST ODR bit position in CTRL REG 1 Register

#define       AXIS_SIZE          ((uint16_t)2)        //!< 2 byte each axis register
#define       REG_SIZE           ((uint16_t)1)        //!< 1 byte each register

/**
 * \def SET_BIT(reg, bit)
 * \brief Macro to set a bit in a register.
 *
 * This macro performs a bitwise OR operation to set the specified bit in the given register.
 */
#define SET_BIT(reg , bit) ( (reg) |= ( 1 << (bit) ) )

/**
 * \def CLEAR_BIT(reg, bit)
 * \brief Macro to clear a bit in a register.
 *
 * This macro performs a bitwise AND operation with the complement of the specified bit
 * to clear the bit in the given register.
 */
#define CLEAR_BIT(reg , bit) ( (reg) &= ~( 1 << (bit) ) )

/**
 * \def CHECK_BIT(reg, bit)
 * \brief Macro to check if a specific bit is set in a register.
 *
 * This macro evaluates to 1 if the specified bit is set in the given register, and 0 otherwise.
 */
#define CHECK_BIT(reg , bit) ( ( (reg) & (1 << (bit) )) != 0 ? (uint8_t)1 : (uint8_t)0 )

/**
 * \brief Macros for masking specific bits in register values.
 * 
 * \details These macros are designed to mask and extract specific bits from register values.
 * 
 * \macros
 *   - `MASK_RATE(reg)`: Masks bits for rate configuration.
 *   - `MASK_INTERUPT(reg)`: Masks bits for interrupt configuration.
 *   - `MASK_RATE_OM(reg)`: Masks bits for rate over mode configuration.
 *   - `MASK_RATE_DO(reg)`: Masks bits for data output rate configuration.
 *   - `MASK_FULLSCALE(reg)`: Masks bits for full-scale configuration.
 */
#define MASK_RATE(reg) ( reg & 0b10000001 )
#define MASK_INTERUPT(reg) (reg & 0b11101110)
#define MASK_RATE_OM(reg) (reg & 0b01100000)
#define MASK_RATE_DO(reg) (reg & 0b00011100)
#define MASK_FULLSCALE(reg) (reg & 0b01100000)


//--------------------------------------------------------------------------------------------------------
// Function definitions
//--------------------------------------------------------------------------------------------------------

FunctionStatus LIS3MDLTR_Constructor(struct LIS3MDLTR *self_ptr, uint8_t devise_id){
  if (self_ptr == NULL){
    return FUNCTION_STATUS_ARGUMENT_ERROR;
  }

  if ( devise_id != 0){
    self_ptr->device_id = devise_id;
  }else{
    self_ptr->device_id = DEFAULT_ADDRESS;
  }

  self_ptr->initialization = true;

  return FUNCTION_STATUS_OK;
}


FunctionStatus LIS3MDLTR_GetFullScaleConfig(struct LIS3MDLTR *self_ptr, full_scale_t* fullscale){
  
  if (self_ptr == NULL){
    return FUNCTION_STATUS_ARGUMENT_ERROR;
  }

  if (self_ptr->initialization == false){
    return FUNCTION_STATUS_DEVICE_NOT_INTIALIZED;
  }

  uint8_t buffer=0;
  i2c_read(self_ptr->device_id, CTRL_REG_2, &buffer, REG_SIZE);

//  printf("newState = %d\n", buffer);

  *fullscale = (full_scale_t)( MASK_FULLSCALE(buffer) >> 5);

//  printf("fullscale = %d\n", *fullscale);

  return FUNCTION_STATUS_OK;
}

FunctionStatus LIS3MDLTR_ChangeOutputDataRate( struct LIS3MDLTR *self_ptr, data_rate_t rate){
  
  if (self_ptr == NULL){
    return FUNCTION_STATUS_ARGUMENT_ERROR;
  }

  if (self_ptr->initialization == false){
    return FUNCTION_STATUS_DEVICE_NOT_INTIALIZED;
  }

  if (rate < RATE_0_625 || rate >= RATE_ENUM_END){
    return FUNCTION_STATUS_BOUNDARY_ERROR;
  }

  uint8_t current_rate = 0 , new_rate = 0;

  i2c_read(self_ptr->device_id, CTRL_REG_1, &current_rate, REG_SIZE);

  new_rate = MASK_RATE(current_rate);

  if ( (rate < RATE_LP) && (rate >= RATE_0_625) ){

    new_rate |= (rate << 2);
  }else{
    new_rate |= ( (rate-RATE_LP) << 5 );
    SET_BIT(new_rate,FAST_ODR_POS);
  }

  //printf("newState = %d\n", new_rate);

  i2c_write(self_ptr->device_id, CTRL_REG_1, &new_rate, REG_SIZE);

  return FUNCTION_STATUS_OK;
}


FunctionStatus LIS3MDLTR_GetOutputDataRate( struct LIS3MDLTR *self_ptr, data_rate_t* datarate){

  if (self_ptr == NULL){
    return FUNCTION_STATUS_ARGUMENT_ERROR;
  }

  if (self_ptr->initialization == false){
    return FUNCTION_STATUS_DEVICE_NOT_INTIALIZED;
  }

  uint8_t buffer;

  i2c_read(self_ptr->device_id, CTRL_REG_1, &buffer, REG_SIZE);

  if( CHECK_BIT(buffer, FAST_ODR_POS) ){
    *datarate = ( ( MASK_RATE_OM(buffer) >> 5 ) + RATE_LP );
  }else{
    *datarate = ( MASK_RATE_DO(buffer) >> 2 );
  }
  //printf("datarate = %d\n", *datarate);

  return FUNCTION_STATUS_OK;
}


FunctionStatus LIS3MDLTR_ChangeInteruptPinStatus( struct LIS3MDLTR *self_ptr, interupt_status_t interupt_status){
  
  if (self_ptr == NULL){
    return FUNCTION_STATUS_ARGUMENT_ERROR;
  }

  if (self_ptr->initialization == false){
    return FUNCTION_STATUS_DEVICE_NOT_INTIALIZED;
  }

  if ( !(interupt_status == ENABLE ||  interupt_status == DISABLE) ){
    return FUNCTION_STATUS_BOUNDARY_ERROR;
  }

  uint8_t current_interupt_status = 0 , new_interupt_status = 0;

  i2c_read(self_ptr->device_id, INT_CFG, &current_interupt_status, REG_SIZE);

  new_interupt_status = MASK_INTERUPT(current_interupt_status);

  new_interupt_status |= interupt_status ;

  //printf("newState = %d\n", new_interupt_status);

  i2c_write(self_ptr->device_id, INT_CFG, &new_interupt_status, REG_SIZE);

  return FUNCTION_STATUS_OK;
}


FunctionStatus LIS3MDLTR_ReadAxis(struct LIS3MDLTR *self_ptr, axis_t axis_to_read, uint16_t* data_ptr){

  if (self_ptr == NULL){
    return FUNCTION_STATUS_ARGUMENT_ERROR;
  }

  if (self_ptr->initialization == false){
    return FUNCTION_STATUS_DEVICE_NOT_INTIALIZED;
  }

  if (axis_to_read > AXIS_Z || axis_to_read < AXIS_X){
    return FUNCTION_STATUS_BOUNDARY_ERROR;
  }

  uint8_t buffer[2] = {0,0};

  i2c_read(self_ptr->device_id, axis_to_read, buffer, AXIS_SIZE);
  
  *data_ptr = (uint16_t)((buffer[1] << 8) | buffer[0]);

  //printf("AxisData = %d\n", *data_ptr);

  return FUNCTION_STATUS_OK;
}
