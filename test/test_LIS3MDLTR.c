#define TEST
#ifdef TEST

#include "unity.h"
#include "mock_i2c.h"

#include "LIS3MDLTR.h"

#include <stdlib.h>
#include <stdio.h>

struct LIS3MDLTR * _lis3mdltr_ptr;

void setUp(void)
{
    _lis3mdltr_ptr = malloc(sizeof(struct LIS3MDLTR));

    _lis3mdltr_ptr->initialization = false;
    _lis3mdltr_ptr->device_id = 0;
}

void tearDown(void)
{
    free(_lis3mdltr_ptr);
}


//============================ LIS3MDLTR_Construct Test ==================================

void test_LIS3MDLTR_Construct_NULL_Argument_Passed_Failed(void){

    FunctionStatus status = LIS3MDLTR_Constructor(NULL, DEFAULT_ADDRESS);

    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_ARGUMENT_ERROR);
}

void test_LIS3MDLTR_Construct_Fail_Default_Address_Set(void){

    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr , 0);

    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->device_id, DEFAULT_ADDRESS);

}


//========================= LIS3MDLTR_GetFullScaleConfig Test =============================

void test_LIS3MDLTR_GetFullScaleConfig_GET_SCALE_4G_Succeed(void){

    // First consrtuct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr,DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t buffer=0;
    uint8_t currentScaleFromSensor = 0b00000100;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x21, &buffer, 1, 1);
    i2c_read_ReturnThruPtr_buffer(&currentScaleFromSensor);

    full_scale_t *fullscale;

    status = LIS3MDLTR_GetFullScaleConfig(_lis3mdltr_ptr, fullscale);
    TEST_ASSERT_EQUAL(*fullscale, SCLAE_4G);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);

}

void test_LIS3MDLTR_GetFullScaleConfig_GET_SCALE_12G_Succeed(void){

    // First consrtuct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr,DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t buffer=0;
    uint8_t currentScaleFromSensor = 0b01001100;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x21, &buffer, 1, 1);
    i2c_read_ReturnThruPtr_buffer(&currentScaleFromSensor);

    full_scale_t *fullscale;

    status = LIS3MDLTR_GetFullScaleConfig(_lis3mdltr_ptr, fullscale);
    TEST_ASSERT_EQUAL(*fullscale, SCALE_12G);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);

}


//======================== LIS3MDLTR_ChangeOutputDataRange Test ===========================

void test_LIS3MDLTR_ChangeOutputDataRange_SET_RANGE_0_625_Succeed(void){

    // First construct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr, DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    // Then continue the test
    uint8_t currentStateToRead = 0;
    uint8_t currentStateExpectedValueFromSensor = 0b11000101;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x20, &currentStateToRead, 1, 1);
    i2c_read_ReturnThruPtr_buffer(&currentStateExpectedValueFromSensor);


    uint8_t expectedCtrlRegDataToWrite = 0b10000001;

    i2c_write_Expect(_lis3mdltr_ptr->device_id, 0x20, &expectedCtrlRegDataToWrite, 1);

    status = LIS3MDLTR_ChangeOutputDataRate(_lis3mdltr_ptr, RATE_0_625);

    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
}

void test_LIS3MDLTR_ChangeOutputDataRange_SET_RANGE_LP_Secceed(void){

    //First Constructor the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr, DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t currentStateToRead = 0;
    uint8_t currentStateExpectedValueFromSensor = 0b11000110;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x20, &currentStateToRead,1,1);
    i2c_read_ReturnThruPtr_buffer(&currentStateExpectedValueFromSensor);


    uint8_t expectedCtrlRageDataToWrite = 0b10000010;

    i2c_write_Expect(_lis3mdltr_ptr->device_id, 0x20, &expectedCtrlRageDataToWrite,1);
    status = LIS3MDLTR_ChangeOutputDataRate(_lis3mdltr_ptr, RATE_LP);

    TEST_ASSERT_EQUAL(status,FUNCTION_STATUS_OK);
}

void test_LIS3MDLTR_ChangeOutputDataRange_SET_RANGE_UHP_Secceed(void){

    //First Constructor the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr, DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t currentStateToRead = 0;
    uint8_t currentStateExpectedValueFromSensor = 0b11110110;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x20, &currentStateToRead,1,1);
    i2c_read_ReturnThruPtr_buffer(&currentStateExpectedValueFromSensor);


    uint8_t expectedCtrlRageDataToWrite = 0b11100010;

    i2c_write_Expect(_lis3mdltr_ptr->device_id, 0x20, &expectedCtrlRageDataToWrite,1);
    status = LIS3MDLTR_ChangeOutputDataRate(_lis3mdltr_ptr, RATE_UHP);

    TEST_ASSERT_EQUAL(status,FUNCTION_STATUS_OK);
}

void test_LIS3MDLTR_ChangeOutputDataRange_SET_RANGE_END_ENUM_Failed(void){

    //First Constructor the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr, DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //THen continue the test
    status = LIS3MDLTR_ChangeOutputDataRate(_lis3mdltr_ptr, RATE_ENUM_END);

    TEST_ASSERT_EQUAL(status,FUNCTION_STATUS_BOUNDARY_ERROR);
}

//========================= LIS3MDLTR_GetOutputDataRate Test ==============================

void test_LIS3MDLTR_GetOutputDataRate_GET_1_25_Succeed(void){

    // First consrtuct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr,DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t buffer=0;
    uint8_t currentDatarateFromSensor = 0b10000101;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x20, &buffer, 1, 1);
    i2c_read_ReturnThruPtr_buffer(&currentDatarateFromSensor);

    data_rate_t *datarate;

    status = LIS3MDLTR_GetOutputDataRate(_lis3mdltr_ptr, datarate);
    TEST_ASSERT_EQUAL(*datarate, RATE_1_25);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);

}

void test_LIS3MDLTR_GetOutputDataRate_GET_HP_Succeed(void){

    // First consrtuct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr,DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t buffer=0;
    uint8_t currentDatarateFromSensor = 0b11000010;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x20, &buffer, 1, 1);
    i2c_read_ReturnThruPtr_buffer(&currentDatarateFromSensor);

    data_rate_t *datarate;

    status = LIS3MDLTR_GetOutputDataRate(_lis3mdltr_ptr, datarate);
    TEST_ASSERT_EQUAL(*datarate, RATE_HP);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);

}

//====================== LIS3MDLTR_ChangeInteruptPinStatus Test ===========================

void test_LIS3MDLTR_ChangeInteruptPinStatus_SET_Enable_Succeed(void){

    // First construct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr, DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    // Then continue the test
    uint8_t currentStateToRead = 0;
    uint8_t currentStateExpectedValueFromSensor = 0b11101110;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x30, &currentStateToRead, 1, 1);
    i2c_read_ReturnThruPtr_buffer(&currentStateExpectedValueFromSensor);


    uint8_t expectedInteruptRegToWrite = 0b11101111;

    i2c_write_Expect(_lis3mdltr_ptr->device_id, 0x30, &expectedInteruptRegToWrite, 1);

    status = LIS3MDLTR_ChangeInteruptPinStatus(_lis3mdltr_ptr, ENABLE);

    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
}

void test_LIS3MDLTR_ChangeInteruptPinStatus_SET_Disable_Succeed(void){

    // First construct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr, DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    // Then continue the test
    uint8_t currentStateToRead = 0;
    uint8_t currentStateExpectedValueFromSensor = 0b10101011;

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x30, &currentStateToRead, 1, 1);
    i2c_read_ReturnThruPtr_buffer(&currentStateExpectedValueFromSensor);


    uint8_t expectedInteruptRegToWrite = 0b10101010;

    i2c_write_Expect(_lis3mdltr_ptr->device_id, 0x30, &expectedInteruptRegToWrite, 1);

    status = LIS3MDLTR_ChangeInteruptPinStatus(_lis3mdltr_ptr, DISABLE);

    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
}
//============================== LIS3MDLTR_ReadAxis Test ==================================

void test_LIS3MDLTR_ReadAxis_Boundry_Error_Failed(void){

    //First Constructor the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr, DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    uint16_t *expectedAxisDataFromSensor;
    //THen continue the test
    status = LIS3MDLTR_ReadAxis(_lis3mdltr_ptr, 0x27, expectedAxisDataFromSensor);

    TEST_ASSERT_EQUAL(status,FUNCTION_STATUS_BOUNDARY_ERROR);
}

void test_LIS3MDLTR_ReadAxis_GET_Axis_X_Succeed(void){

    // First consrtuct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr,DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t buffer[]={0,0};
    uint8_t currentDatarateFromSensor[] = {0b10000101, 0b10110101};

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x28, buffer, 2, 2);
    i2c_read_ReturnArrayThruPtr_buffer(currentDatarateFromSensor,2);

    uint16_t expectedXAxisData;
    axis_t x = AXIS_X;

    status = LIS3MDLTR_ReadAxis(_lis3mdltr_ptr, x , &expectedXAxisData);
    TEST_ASSERT_EQUAL(expectedXAxisData, 46469);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);

}

void test_LIS3MDLTR_ReadAxis_GET_Axis_Y_Succeed(void){

    // First consrtuct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr,DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t buffer[]={0,0};
    uint8_t currentDatarateFromSensor[] = {0b11111111, 0b00000000};

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x2A, buffer, 2, 2);
    i2c_read_ReturnArrayThruPtr_buffer(currentDatarateFromSensor,2);

    uint16_t expectedYAxisData;
    axis_t y = AXIS_Y;

    status = LIS3MDLTR_ReadAxis(_lis3mdltr_ptr, y , &expectedYAxisData);
    TEST_ASSERT_EQUAL(expectedYAxisData, 255);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);

}

void test_LIS3MDLTR_ReadAxis_GET_Axis_Z_Succeed(void){

    // First consrtuct the instance
    FunctionStatus status = LIS3MDLTR_Constructor(_lis3mdltr_ptr,DEFAULT_ADDRESS);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);
    TEST_ASSERT_EQUAL(_lis3mdltr_ptr->initialization, true);

    //Then continue the test
    uint8_t buffer[]={0,0};
    uint8_t currentDatarateFromSensor[] = { 0b00000000, 0b11111111};

    i2c_read_ExpectWithArray(_lis3mdltr_ptr->device_id, 0x2C, buffer, 2, 2);
    i2c_read_ReturnArrayThruPtr_buffer(currentDatarateFromSensor,2);

    uint16_t expectedZAxisData;
    axis_t z = AXIS_Z;

    status = LIS3MDLTR_ReadAxis(_lis3mdltr_ptr, z , &expectedZAxisData);
    TEST_ASSERT_EQUAL(expectedZAxisData, 65280);
    TEST_ASSERT_EQUAL(status, FUNCTION_STATUS_OK);

}
#endif // TEST
