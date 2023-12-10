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


//--------------------------------------------------------------------------------------------------------
// Constant and macro definitions
//--------------------------------------------------------------------------------------------------------
#define       X_ADDRESS_REG      ((uint8_t)0x28)      //!< Address of X register
#define       Y_ADDRESS_REG      ((uint8_t)0x2A)      //!< Address of Y register
#define       Z_ADDREDD_REG      ((uint8_t)0x2C)      //!< Address of Z register

#define       DEFAULT_ADDRESS    ((uint8_t)0x3d)      //!< Default bus address

//--------------------------------------------------------------------------------------------------------
// Type definitions
//--------------------------------------------------------------------------------------------------------

//structure pf LIS3MDLTR sensor
struct LIS3MDLTR{
  bool initialization;
  uint8_t device_id; //buss_address of sensor
};

//Function status for error handeling
typedef enum FunctionStatus{
  FUNCTION_STATUS_OK = 0,
  FUNCTION_STATUS_ARGUMENT_ERROR,
  FUNCTION_STATUS_DEVICE_NOT_INTIALIZED,
  FUNCTION_STATUS_BOUNDARY_ERROR,
  FUNCTION_STATUS_ERROR
}FunctionStatus;

typedef enum full_scale_t {
  SCLAE_4G = 0x00,                      //!< +/-4 gauss scale
  SCLAE_8G = 0x01,                      //!< +/-8 gauss scale
  SCALE_12G = 0x02,                     //!< +/-12 gauss scale
  SCALE_16G = 0x03                      //!< +/-16 gauss scale
}full_scale_t;

typedef enum data_rate_t {
  RATE_0_625 = 0,                   //!< Data rate 0.625
  RATE_1_25,                        //!< Data rate 1.25
  RATE_2_5,                         //!< Data rate 2.5
  RATE_5,                           //!< Data rate 5
  RATE_10,                          //!< Data rate 10
  RATE_20,                          //!< Data rate 20
  RATE_40,                          //!< Data rate 40
  RATE_80,                          //!< Data rate 80

  RATE_LP,                          //!< Data rate 1000
  RATE_MP,                          //!< Data rate 560
  RATE_HP,                          //!< Data rate 300
  RATE_UHP,                         //!< Data rate 155
  RATE_ENUM_END                     //!< End of data rate
}data_rate_t;

typedef enum interupt_status_t {
  DISABLE = 0,
  ENABLE = 1 
}interupt_status_t;

typedef enum axis_t {
  AXIS_X = X_ADDRESS_REG,
  AXIS_Y = Y_ADDRESS_REG,
  AXIS_Z = Z_ADDREDD_REG
}axis_t;

//--------------------------------------------------------------------------------------------------------
// Functions declartions
//--------------------------------------------------------------------------------------------------------

//Constructor for sensor structure
FunctionStatus LIS3MDLTR_Constructor(struct LIS3MDLTR *self_ptr, uint8_t device_id);

//Retrieve the device’s full-scale configuration
FunctionStatus LIS3MDLTR_GetFullScaleConfig(struct LIS3MDLTR *self_ptr, full_scale_t* fullscale);

//Set the device’s output data rate
FunctionStatus LIS3MDLTR_ChangeOutputDataRate( struct LIS3MDLTR *self_ptr, data_rate_t rate);

//Retrieve the device’s output data rate
FunctionStatus LIS3MDLTR_GetOutputDataRate( struct LIS3MDLTR *self_ptr, data_rate_t* datarate);

//Enable or disable the device’s interrupt pin
FunctionStatus LIS3MDLTR_ChangeInteruptPinStatus( struct LIS3MDLTR *self_ptr, interupt_status_t interupt_status);

//Read the output data of a specific axis
FunctionStatus LIS3MDLTR_ReadAxis(struct LIS3MDLTR *self_ptr, axis_t axis_to_read, uint16_t* data_ptr);

//--------------------------------------------------------------------------------------------------------
// Function definitions
//--------------------------------------------------------------------------------------------------------

