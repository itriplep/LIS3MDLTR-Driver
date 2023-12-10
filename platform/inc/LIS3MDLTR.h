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


#ifndef INC_LIS3MDLTR_H_
#define INC_LIS3MDLTR_H_

/**
 * LIS3MDLTR implementation
 * \defgroup LIS3MDLTR
 * \brief Driver module for LIS3MDLTR 3-Axis Magnetometer sensor
 * \ingroup platform
 * 
 * This is the driver module for LIS3MDLTR 3-Axis magnetometer sensor
 * It uses the I2C communication to get 3-Axis and Also get/set registers of sensors.
 * @{
*/

//--------------------------------------------------------------------------------------------------------
// Include files
//--------------------------------------------------------------------------------------------------------
// Compiler Includes
// All include files that are provided by the compiler directly
#include <stdint.h>                     // include to use integer types 
#include <stdbool.h>                    // include to use standard boolean

//Project Includes
//All include files that are provided by the project


//--------------------------------------------------------------------------------------------------------
// Constant definitions
//--------------------------------------------------------------------------------------------------------

#define       X_ADDRESS_REG      ((uint8_t)0x28)      //!< Address of X register
#define       Y_ADDRESS_REG      ((uint8_t)0x2A)      //!< Address of Y register
#define       Z_ADDREDD_REG      ((uint8_t)0x2C)      //!< Address of Z register

#define       DEFAULT_ADDRESS    ((uint8_t)0x3d)      //!< Default bus address

//--------------------------------------------------------------------------------------------------------
// Type definitions
//--------------------------------------------------------------------------------------------------------

/**
 * \class LIS3MDLTR
 * \brief Represents the configuration and state of a LIS3MDLTR sensor.
 *
 * DETAILED DESCRIPTION
 *
 * \members
 *   - `initialization`: A boolean indicating whether the sensor is initialized.
 *   - `device_id`: The bus address of the sensor.
 */
struct LIS3MDLTR{
  bool initialization;
  uint8_t device_id; //buss_address of sensor
};

/**
 * \enum FunctionStatus
 * \brief Enumeration representing the status of a function.
 *
 * This enumeration defines different status codes that a function may return,
 * including success (OK), argument error, uninitialized device, boundry error, and general error.
 */
typedef enum FunctionStatus {
  FUNCTION_STATUS_OK = 0,
  FUNCTION_STATUS_ARGUMENT_ERROR,
  FUNCTION_STATUS_DEVICE_NOT_INTIALIZED,
  FUNCTION_STATUS_BOUNDARY_ERROR,
  FUNCTION_STATUS_ERROR
}FunctionStatus;

/**
 * \enum LIS3MDLTR full-scale configuration
 * \brief Enumeration representing different full-scale configurations for the LIS3MDLTR magnetometer.
 *
 * This enumeration defines four possible scales for the magnetometer: +/-4, +/-8, +/-12, and +/-16 gauss.
 */
typedef enum full_scale_t {
  SCLAE_4G = 0x00,                      //!< +/-4 gauss scale
  SCLAE_8G = 0x01,                      //!< +/-8 gauss scale
  SCALE_12G = 0x02,                     //!< +/-12 gauss scale
  SCALE_16G = 0x03                      //!< +/-16 gauss scale
}full_scale_t;

/**
 * \enum data_rate_t
 * \brief Enumeration representing different data rates for a sensor.
 *
 * This enumeration defines various data rates ranging from 0.625 to 1000 Hz,
 * with additional symbolic values for specific rates (LP, MP, HP, UHP).
 * RATE_ENUM_END is included to mark the end of the data rate enumeration.
 */
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


/**
 * \enum intrupt_status_t
 * \brief Enumeration representing interrupt status (ENABLE or DISABLE).
 *
 * This enumeration defines two states, ENABLE and DISABLE, to represent the
 * status of an interrupt pin of sensor is enabled or disabled.
 */
typedef enum interupt_status_t {
  DISABLE = 0,
  ENABLE = 1 
}interupt_status_t;


/**
 * \enum LIS3MDLYR axis's register address
 * \brief Enumeration representing register addresses for LIS3MDLYR accelerometer axes.
 *
 * This enumeration maps each axis (X, Y, Z) to its corresponding register address
 * in the LIS3MDLYR accelerometer.
*/
typedef enum axis_t {
  AXIS_X = X_ADDRESS_REG,
  AXIS_Y = Y_ADDRESS_REG,
  AXIS_Z = Z_ADDREDD_REG
}axis_t;

//--------------------------------------------------------------------------------------------------------
// Functions declartions
//--------------------------------------------------------------------------------------------------------

/**
 * LIS3MDLTR_Constructor
 * \brief Initializes the LIS3MDLTR sensor object.
 * 
 * Detailed Description
 * 
 * \param      self_ptr            Pointer to the LIS3MDLTR structure to be initialized
 * \param      device_id           Device identifier for the LIS3MDLTR sensor
 *
 * \return	   FunctionStatus       @arg FUNCTION_STATUS_OK if the operation was successful
 *                                  @arg FUNCTION_STATUS_ARGUMENT_ERROR if self_ptr is NULL
 *                                  @arg Other error codes can be defined based on the specific implementation
 * 
 * --------------------------------------------------------------------------------------------------------------------
 * This function initializes the LIS3MDLTR sensor object. It sets the device identifier, and if a valid
 * device_id is provided, it uses it; otherwise, it defaults to the DEFAULT_ADDRESS. The initialization flag
 * is set to true, indicating that the sensor object has been properly initialized.
 * 
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus LIS3MDLTR_Constructor ( struct LIS3MDLTR *self_ptr , uint8_t devise_id );


/**
 * LIS3MDLTR_GetFullScaleConfig
 * \brief Gets the full-scale configuration setting from the LIS3MDLTR sensor.
 * 
 * Detailed Description
 * 
 * \param      self_ptr            Pointer to the LIS3MDLTR structure to read data from
 * \param      fullscale           Pointer to a full_scale_t variable where the full-scale setting will be stored
 *
 * \return	   FunctionStatus       @arg FUNCTION_STATUS_OK if the operation was successful
 *                                  @arg FUNCTION_STATUS_ARGUMENT_ERROR if self_ptr is NULL
 *                                  @arg FUNCTION_STATUS_DEVICE_NOT_INTIALIZED if the sensor is not initialized
 * 
 * --------------------------------------------------------------------------------------------------------------------
 * This function retrieves the full-scale configuration setting from the LIS3MDLTR sensor. It performs necessary
 * argument checks, reads the control register(from CTRL_REG2 register), and extracts the full-scale information 
 * based on the sensor's configuration. The result is stored in the provided fullscale variable.
 * 
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus LIS3MDLTR_GetFullScaleConfig(struct LIS3MDLTR *self_ptr, full_scale_t* fullscale);

/**
 * LIS3MDLTR_ChangeOutputDataRate
 * \brief Changes the output data rate setting on the LIS3MDLTR sensor.
 * 
 * Detailed Description
 * 
 * \param      self_ptr            Pointer to LIS3MDLTR structure to read data from
 * \param      rate                Desired data rate setting (data_rate_t enum)
 *
 * \return	   FunctionStatus       @arg FUNCTION_STATUS_OK if the operation was successful
 *                                  @arg FUNCTION_STATUS_ARGUMENT_ERROR if self_ptr is NULL
 *                                  @arg FUNCTION_STATUS_DEVICE_NOT_INTIALIZED if the sensor is not initialized
 *                                  @arg FUNCTION_STATUS_BOUNDARY_ERROR if the rate is out of bounds
 * 
 * --------------------------------------------------------------------------------------------------------------------
 * This function changes the output data rate setting on the LIS3MDLTR sensor. It performs necessary
 * argument checks, reads the current rate configuration(from CTRL_REG1 register), updates the desired rate, and 
 * writes the new configuration back to the sensor using I2C communication. The new rate is determined based on the
 * provided rate parameter and sensor configuration.
 * 
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus LIS3MDLTR_ChangeOutputDataRate( struct LIS3MDLTR *self_ptr, data_rate_t rate);


/**
 * LIS3MDLTR_GetOutputDataRate
 * \brief Gets the output data rate setting from the LIS3MDLTR sensor.
 * 
 * Detailed Description
 * 
 * \param      self_ptr            Pointer to LIS3MDLTR structure to read data from
 * \param      datarate            Pointer to a data_rate_t variable where the data rate setting will be stored
 *
 * \return	   FunctionStatus       @arg FUNCTION_STATUS_OK if the operation was successful
 *                                  @arg FUNCTION_STATUS_ARGUMENT_ERROR if self_ptr is NULL
 *                                  @arg FUNCTION_STATUS_DEVICE_NOT_INTIALIZED if the sensor is not initialized
 * 
 * --------------------------------------------------------------------------------------------------------------------
 * This function retrieves the output data rate setting from the LIS3MDLTR sensor. It performs necessary
 * argument checks, reads the control register(from CTRL_REG1 register), and extracts the data rate information based 
 * on the sensor's configuration. The result is stored in the provided datarate variable.
 * 
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus LIS3MDLTR_GetOutputDataRate( struct LIS3MDLTR *self_ptr, data_rate_t* datarate);


/**
 * LIS3MDLTR_ChangeIntruptPinStatus
 * \brief Changes the status of the interrupt pin on the LIS3MDLTR sensor.
 * 
 * Detailed Description
 * 
 * \param      self_ptr            Pointer to LIS3MDLTR structure to read data from
 * \param      intrupt_status      Desired status of the interrupt pin (ENABLE or DISABLE)
 *
 * \return	   FunctionStatus       @arg FUNCTION_STATUS_OK if the operation was successful
 *                                  @arg FUNCTION_STATUS_ARGUMENT_ERROR if self_ptr is NULL
 *                                  @arg FUNCTION_STATUS_DEVICE_NOT_INTIALIZED if the sensor is not initialized
 *                                  @arg FUNCTION_STATUS_BOUNDARY_ERROR if intrupt_status is not ENABLE or DISABLE
 * 
 * --------------------------------------------------------------------------------------------------------------------
 * This function changes the status of the interrupt pin on the LIS3MDLTR sensor. It performs necessary
 * argument checks, reads the current interrupt configuration(from INT_CFG register), updates the desired status, and 
 * writes the new configuration back to the sensor using I2C communication.
 * 
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus LIS3MDLTR_ChangeInteruptPinStatus( struct LIS3MDLTR *self_ptr, interupt_status_t intrupt_status);


/**
 * LIS3MDLTR_ReadAxis
 * \brief Reads magnetic field data for a specified axis from the LIS3MDLTR sensor.
 * 
 * Detailed Description
 * 
 * \param      self_ptr            Pointer to LIS3MDLTR structure to read data from
 * \param      axis_to_read        The axis for which data needs to be read (AXIS_X, AXIS_Y, or AXIS_Z)
 * \param      data_ptr            Pointer to a uint16_t variable where the read data will be stored
 *
 * \return	   FunctionStatus       @arg FUNCTION_STATUS_OK if the operation was successful
 *                                  @arg FUNCTION_STATUS_ARGUMENT_ERROR if self_ptr is NULL
 *                                  @arg FUNCTION_STATUS_DEVICE_NOT_INTIALIZED if the sensor is not initialized
 *                                  @arg FUNCTION_STATUS_BOUNDARY_ERROR if the axis_to_read is out of bounds
 *                                  (not within AXIS_X to AXIS_Z)
 * 
 * --------------------------------------------------------------------------------------------------------------------
 * This function reads magnetic field data from the LIS3MDLTR sensor for a specified axis. It performs
 * necessary argument checks, initializes a buffer to store the read data, and reads the data from the sensor
 * using I2C communication. The result is stored in the provided data_ptr.
 * 
 * --------------------------------------------------------------------------------------------------------------------
 */
FunctionStatus LIS3MDLTR_ReadAxis(struct LIS3MDLTR *self_ptr, axis_t axis_to_read, uint16_t* data_ptr);

/** @} */
#endif
