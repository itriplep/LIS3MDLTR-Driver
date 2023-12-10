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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//Project Includes
//All include files that are provided by the project
#include "LIS3MDLTR.h"

//--------------------------------------------------------------------------------------------------------
// Constant and macro definitions
//--------------------------------------------------------------------------------------------------------
#define       CTRL_REG_2         ((uint8_t)0x21)      //!< Address of CTRL REG 2 Register for full-scale

#define       REG_SIZE           ((uint16_t)1)        //!< 1 byte each register

//--------------------------------------------------------------------------------------------------------
// Type definitions
//--------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------
// Functions declartions
//--------------------------------------------------------------------------------------------------------


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

  uint8_t buffer;
  i2c_read(self_ptr->device_id, CTRL_REG_2, &buffer, REG_SIZE);

  *fullscale = (full_scale_t)( MASK_FULLSCALE(buffer) >> 5);
  
  return FUNCTION_STATUS_OK;
}