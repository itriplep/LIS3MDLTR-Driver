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
  FUNCTION_STATUS_ERROR
}FunctionStatus;

//--------------------------------------------------------------------------------------------------------
// Functions declartions
//--------------------------------------------------------------------------------------------------------

//Constructor for sensor structure
FunctionStatus LIS3MDLTR_Constructor(struct LIS3MDLTR *self_ptr, uint8_t device_id);

//Retrieve the device’s full-scale configuration
FunctionStatus LIS3MDLTR_GetFullScaleConfig(struct LIS3MDLTR *self_ptr, uint8_t* fullscale);

//Set the device’s output data rate
FunctionStatus LIS3MDLTR_ChangeOutputDataRate(struct LIS3MDLTR *self_ptr, uint8_t rate);

//Retrieve the device’s output data rate
FunctionStatus LIS3MDLTR_GetOutputDataRate(struct LIS3MDLTR *self_ptr, uint8_t* datarate);

//Enable or disable the device’s interrupt pin
FunctionStatus LIS3MDLTR_ChangeInteruptPinStatus(struct LIS3MDLTR *self_ptr, uint8_t interupt_status);

//Read the output data of a specific axis
FunctionStatus LIS3MDLTR_ReadAxis(struct LIS3MDLTR *self_ptr, uint8_t axis_to_read, uint16_t* data_ptr);

//--------------------------------------------------------------------------------------------------------
// Function definitions
//--------------------------------------------------------------------------------------------------------

