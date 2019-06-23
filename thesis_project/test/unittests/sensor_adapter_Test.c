#include "unity.h"
#include "src/adapter_PAC1720/adapter_PAC1720.h"

#include "lib/i2cmaster/Mocki2cmaster.h"  
#include "lib/delay/Mockuser_delay.h" 
#include "lib/circular_buffer/Mockcircular_buffer.h" 

#include <stdio.h>

/** Helper function prototypes */
void reset_values(void);

// /** Provide function pointers */
// typedef int8_t (*adapter_i2c_write) (const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);
// typedef int8_t (*adapter_i2c_read) (const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);
// typedef void (*adapter_delay) (uint32_t period);
// typedef int8_t (*sensor_address_out_of_range) (const uint8_t address);
// typedef int8_t (*channels_out_of_range) (const ACTIVE_CHANNELS channels);

// /** Declare functions */
// adapter_i2c_write adapter_i2c_write_func;
// adapter_i2c_read adapter_i2c_read_func;
// adapter_delay adapter_delay_func;
// sensor_address_out_of_range sensor_address_out_of_range_func;
// channels_out_of_range channels_out_of_range_func;

/** Struct definition */
struct PAC1720_device dev;

// void setUp(void) {
//     // Get function pointers from declaration
//     const (**test_fptr_field)[]         = (void*)  get_ADAPTER_TEST_FPTR_FIELD();
//     // Assign function pointers function declares
//     adapter_i2c_write_func              = (adapter_i2c_write) test_fptr_field[0];
//     adapter_i2c_read_func               = (adapter_i2c_read) test_fptr_field[1];
//     adapter_delay_func                  = (adapter_delay) test_fptr_field[2];
//     sensor_address_out_of_range_func    = (sensor_address_out_of_range) test_fptr_field[3];
//     channels_out_of_range_func          = (channels_out_of_range) test_fptr_field[4];
// }

void tearDown(void) {}

/* Reset the struct values after test */
void reset_values(void){
    dev.channels = 0;
    dev.sensor_address = 0;
    dev.write = dev.read = NULL;
    dev.delay_ms = NULL;
}

void test_adapter_init_PAC1720(void){
    // /* Set up dummy inputs */
    // uint8_t dummy_address = 0x28;
    // ACTIVE_CHANNELS dummy_channels = BOTH_CHANNELS;
    // /* Test nullpointer failure */
    // TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(NULL, dummy_address, dummy_channels));
    // /* Test address out of range */
    // TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, 0, dummy_channels));
    // TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, 0x2F, dummy_channels));
    // /* Test channels out of range */
    // TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_address, 0));
    // TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_address, 4));
    // /* Validate init function */
    // TEST_ASSERT_EQUAL(PAC1720_OK, adapter_init_PAC1720(&dev, dummy_address, dummy_channels));
    // TEST_ASSERT_EQUAL_HEX8(dummy_address, dev.sensor_address);
    // TEST_ASSERT_EQUAL_HEX8(dummy_channels, dev.channels);

    // reset_values();
}

void test_adapter_i2c_write(void){
    // circular_test();
}

void test_adapter_i2c_read(void){
    
}

void test_sensor_address_out_of_range(void){

}

void test_channels_out_of_range(void){

}

void test_fail(void){
    char msg[500];
    uint8_t x = 0;
    sprintf(msg, "Test: %x\n", x);
    // TEST_FAIL_MESSAGE(msg);
}