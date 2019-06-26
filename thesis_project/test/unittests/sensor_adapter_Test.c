#include "unity.h"
#include "src/adapter_PAC1720/adapter_PAC1720.h"
#include <stdio.h>

/** Sensor test- device struct  */
struct PAC1720_device dev;

/** Helper function prototypes */
void reset_values(void);

/* Verification parameters set by spies */
uint8_t mock_i2c_start_call;
uint8_t mock_i2c_start_arg;
uint8_t mock_i2c_start_wait_call;
uint8_t mock_i2c_start_wait_arg;
uint8_t mock_i2c_rep_start_call;
uint8_t mock_i2c_rep_start_arg;
uint8_t mock_i2c_stop_call;
uint8_t mock_i2c_write_call;
uint8_t mock_i2c_write_arg;
uint8_t mock_i2c_readAck_call;
uint8_t mock_i2c_readNak_call;

uint32_t mock_delay_arg;
uint8_t  mock_delay_call;

/** Field- Bus communication spies */
void mock_i2c_init(void){

}

unsigned char mock_i2c_start(unsigned char address){
    mock_i2c_start_call++;
    mock_i2c_start_arg = address;
    return PAC1720_OK;
}

void mock_i2c_start_wait(unsigned char address){
    mock_i2c_start_wait_call++;
    mock_i2c_start_wait_arg = address;
}

unsigned char mock_i2c_rep_start(unsigned char address){
    mock_i2c_rep_start_call++;
    mock_i2c_rep_start_arg = address;
    return PAC1720_OK;
}

void mock_i2c_stop(void){
    mock_i2c_stop_call++;
}

unsigned char mock_i2c_write( unsigned char data ){
    mock_i2c_write_call++;
    mock_i2c_write_arg = data;
	return PAC1720_OK;
}

unsigned char mock_i2c_readAck(void){
    mock_i2c_readAck_call++;
    return 0xDD;
}

unsigned char mock_i2c_readNak(void){
    mock_i2c_readNak_call++;
    return 0xDE;
}

/* External delay function spy */
void mock_user_delay(uint32_t period){
    mock_delay_arg= period;
    mock_delay_call++;
}

/** Field- Bus communication struct from external */
struct BUS_INTERFACE_I2C dummy_i2c = {
    .init       = &mock_i2c_init,
    .stop       = &mock_i2c_stop,
    .start      = &mock_i2c_start,
    .repStart   = &mock_i2c_rep_start,
    .startWait  = &mock_i2c_start_wait,
    .write      = &mock_i2c_write,
    .readAck    = &mock_i2c_readAck,
    .readNak    = &mock_i2c_readNak
};

/** Provide function pointers */
typedef int8_t      (*adapter_i2c_write)            (const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);
typedef int8_t      (*adapter_i2c_read)             (const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);
typedef void        (*adapter_delay)                (uint32_t period);
typedef bool        (*sensor_address_out_of_range)  (const uint8_t address);
typedef bool        (*channels_out_of_range)        (const ACTIVE_CHANNELS channels);
typedef uint8_t     (*poll_i2c)                     (const struct BUS_INTERFACE_I2C *i2c_ptr, uint8_t loop_var, uint8_t *addresses);

/** Declare functions */
adapter_i2c_write               adapter_i2c_write_func;
adapter_i2c_read                adapter_i2c_read_func;
adapter_delay                   adapter_delay_func;
sensor_address_out_of_range     sensor_address_out_of_range_func;
channels_out_of_range           channels_out_of_range_func;
poll_i2c                        poll_i2c_func;

void setUp(void) {
    // Get function pointers from declaration
    const void* (**test_fptr_field)[]   = (void*) get_ADAPTER_TEST_FPTR_FIELD();
    // Assign function pointers function declares
    adapter_i2c_write_func              = (adapter_i2c_write)               test_fptr_field[0];
    adapter_i2c_read_func               = (adapter_i2c_read)                test_fptr_field[1];
    adapter_delay_func                  = (adapter_delay)                   test_fptr_field[2];
    sensor_address_out_of_range_func    = (sensor_address_out_of_range)     test_fptr_field[3];
    channels_out_of_range_func          = (channels_out_of_range)           test_fptr_field[4];
    poll_i2c_func                       = (poll_i2c)                        test_fptr_field[5];
}

void tearDown(void) {}

/* Reset values after test */
void reset_values(void){
    /* Reset struct values */
    dev.name = NULL;
    dev.sensor_address = 0;
    dev.channels = 0;
    dev.configuration_reg = 0;
    dev.conversion_rate_reg = 0;
    dev.one_shot_reg = 0;
    dev.channel_mask_reg = 0;
    dev.high_limit_status_reg = 0;
    dev.low_limit_status_reg = 0;
    dev.source_voltage_sampling_config_reg = 0;
    dev.ch1_current_sense_sampling_config_reg = 0;
    dev.ch2_current_sense_sampling_config_reg = 0;
    dev.sensor_product_id = 0;
    dev.sensor_manufact_id = 0;
    dev.sensor_revision = 0;
    dev.read = dev.write = NULL;                   
    dev.delay_ms = NULL;

    dev.sensor_config_ch1.name = NULL;
    dev.sensor_config_ch1.current_sense_resistor_value = 0;
    dev.sensor_config_ch1.current_sense_sampling_time_reg = 0;
    dev.sensor_config_ch1.current_sense_sampling_average_reg = 0;
    dev.sensor_config_ch1.current_sense_FSR_reg = 0;
    dev.sensor_config_ch1.current_sense_FSC = 0;
    dev.sensor_config_ch1.source_voltage_sampling_time_reg = 0;
    dev.sensor_config_ch1.source_voltage_sampling_average_reg = 0;
    dev.sensor_config_ch1.source_voltage_FSV = 0;
    dev.sensor_config_ch1.power_sense_FSP = 0;
    dev.sensor_config_ch1.current_sense_limit_reg = 0;
    dev.sensor_config_ch1.source_voltage_limit_reg = 0;
    
    dev.ch1_readings.reading_done = false;
    dev.ch1_readings.status = 0;
    dev.ch1_readings.v_sense_voltage_reg = 0;
    dev.ch1_readings.v_source_voltage_reg = 0;
    dev.ch1_readings.power_ratio_reg = 0;
    dev.ch1_readings.res_CURRENT = 0;
    dev.ch1_readings.res_POWER = 0;
    dev.ch1_readings.res_SENSE_VOLTAGE = 0;
    dev.ch1_readings.res_SOURCE_VOLTAGE = 0;

    /* Reset verification parameters set by spies */
    mock_i2c_start_call      = 0;
    mock_i2c_start_arg       = 0;
    mock_i2c_rep_start_call  = 0;
    mock_i2c_start_wait_call = 0;
    mock_i2c_start_wait_arg  = 0;
    mock_i2c_rep_start_arg   = 0;
    mock_i2c_stop_call       = 0;
    mock_i2c_write_call      = 0;
    mock_i2c_write_arg       = 0;
    mock_i2c_readAck_call    = 0;
    mock_i2c_readNak_call    = 0;
    mock_delay_arg           = 0;
    mock_delay_call          = 0;
}

void test_adapter_find_sensors(void){

}

void test_poll_i2c(void){

}

void test_adapter_init_PAC1720(void){
    reset_values();
    /* Set up dummy inputs */
    uint8_t dummy_address = 0x28;
    float dummy_resistance_ch1 = 0.8f;
    float dummy_resistance_ch2 = 1600.0f;
    ACTIVE_CHANNELS dummy_channels = BOTH_CHANNELS;
    char *dummy_name = "DEV";
    char *dummy_CH1_name = "CH1DEV";
    char *dummy_CH2_name = "CH2DEV";
    /* Test nullpointer failure */
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(NULL, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, &mock_user_delay, dummy_address, dummy_resistance_ch1, dummy_resistance_ch2, dummy_channels));
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, NULL, &mock_user_delay, dummy_address, dummy_resistance_ch1, dummy_resistance_ch2, dummy_channels));
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, NULL, dummy_address, dummy_resistance_ch1, dummy_resistance_ch2, dummy_channels));
    /* Test naming */
    TEST_ASSERT_EQUAL(PAC1720_OK, adapter_init_PAC1720(&dev, NULL, NULL, NULL, &dummy_i2c, &mock_user_delay, dummy_address, dummy_resistance_ch1, dummy_resistance_ch2, dummy_channels));
    TEST_ASSERT_EQUAL(PAC1720_OK, adapter_init_PAC1720(&dev, NULL, dummy_CH1_name, NULL, &dummy_i2c, &mock_user_delay, dummy_address, dummy_resistance_ch1, dummy_resistance_ch2, dummy_channels));
    /* Test address out of range */
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, &mock_user_delay, 0x17, dummy_resistance_ch1, dummy_resistance_ch2, dummy_channels));
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, &mock_user_delay, 0x2F, dummy_resistance_ch1, dummy_resistance_ch2, dummy_channels));
    /* Test resistance value == 0 */
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, &mock_user_delay, dummy_address, 0, dummy_resistance_ch2, dummy_channels));
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, &mock_user_delay, dummy_address, dummy_resistance_ch1, 0, dummy_channels));
    /* Test channels out of range */
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, &mock_user_delay, dummy_address, dummy_resistance_ch1, dummy_resistance_ch2, 0));
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, &mock_user_delay, dummy_address, dummy_resistance_ch1, dummy_resistance_ch2, 4));
    /* Verify init function */
    TEST_ASSERT_EQUAL(PAC1720_OK, adapter_init_PAC1720(&dev, dummy_name, dummy_CH1_name, dummy_CH2_name, &dummy_i2c, &mock_user_delay, dummy_address, dummy_resistance_ch1, dummy_resistance_ch2, dummy_channels));
    TEST_ASSERT_EQUAL_HEX8(dummy_address, dev.sensor_address);
    TEST_ASSERT_EQUAL_FLOAT(dummy_resistance_ch1, dev.sensor_config_ch1.current_sense_resistor_value);
    TEST_ASSERT_EQUAL_FLOAT(dummy_resistance_ch2, dev.sensor_config_ch2.current_sense_resistor_value);
    TEST_ASSERT_EQUAL_STRING(dummy_name, dev.name);
    TEST_ASSERT_EQUAL_STRING(dummy_CH1_name, dev.sensor_config_ch1.name);
    TEST_ASSERT_EQUAL_STRING(dummy_CH2_name, dev.sensor_config_ch2.name);
    TEST_ASSERT_EQUAL_HEX8(dummy_channels, dev.channels);
    TEST_ASSERT_EQUAL_PTR(adapter_i2c_write_func, dev.write);
    TEST_ASSERT_EQUAL_PTR(adapter_i2c_read_func, dev.read);
    TEST_ASSERT_EQUAL_PTR(adapter_delay_func, dev.delay_ms);
}

void test_adapter_i2c_write(void){
    reset_values();
    /* Set up dummy inputs */
    uint8_t dummy_address = 0x28;
    uint8_t dummy_address_return = (dummy_address << I2C_ADDRESS_SHIFT) + I2C_WRITE;
    uint8_t dummy_reg_address = 0x11;
    uint8_t dummy_data[2] = {0xAA, 0xBB};
    uint8_t dummy_len = sizeof(dummy_data);
    /* Execute function */
    TEST_ASSERT_EQUAL(PAC1720_OK, adapter_i2c_write_func(dummy_address, dummy_reg_address, dummy_data, dummy_len));
    /* Evaluate spy parameters */
    TEST_ASSERT_EQUAL_HEX8(dummy_address_return, mock_i2c_start_wait_arg);
    TEST_ASSERT_EQUAL(1,mock_i2c_start_wait_call);
    TEST_ASSERT_EQUAL_HEX8(dummy_data[1], mock_i2c_write_arg);
    TEST_ASSERT_EQUAL(3, mock_i2c_write_call);
    TEST_ASSERT_EQUAL(1,mock_i2c_stop_call);
}   

void test_adapter_i2c_read(void){
    reset_values();
    /* Set up dummy inputs */
    uint8_t dummy_address = 0x28;
    uint8_t dummy_address_write_return = (dummy_address << I2C_ADDRESS_SHIFT) + I2C_WRITE;
    uint8_t dummy_address_read_return = (dummy_address << I2C_ADDRESS_SHIFT) + I2C_READ;
    uint8_t dummy_reg_address = 0x11;
    uint8_t dummy_data[3] = {0};
    uint8_t dummy_len = sizeof(dummy_data);
    /* Execute function */
    TEST_ASSERT_EQUAL_HEX8(PAC1720_OK, adapter_i2c_read_func(dummy_address, dummy_reg_address, dummy_data, dummy_len));
    /* Evaluate spy parameters */
    TEST_ASSERT_EQUAL_HEX8(dummy_address_write_return, mock_i2c_start_wait_arg);
    TEST_ASSERT_EQUAL(1, mock_i2c_start_wait_call);
    TEST_ASSERT_EQUAL_HEX8(dummy_reg_address, mock_i2c_write_arg);
    TEST_ASSERT_EQUAL(1, mock_i2c_write_call);
    TEST_ASSERT_EQUAL_HEX8(dummy_address_read_return, mock_i2c_rep_start_arg);
    TEST_ASSERT_EQUAL(1, mock_i2c_rep_start_call);
    TEST_ASSERT_EQUAL(2, mock_i2c_readAck_call);
    TEST_ASSERT_EQUAL(1, mock_i2c_readNak_call);
    TEST_ASSERT_EQUAL(1,mock_i2c_stop_call);
    /* Evaluate array reading */
    uint8_t test_arr[3] = {0xDD, 0xDD, 0xDE};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(test_arr, dummy_data, dummy_len);
}

void test_adapter_delay(void){
    uint32_t dummy_period = 1500;
    adapter_delay_func(dummy_period);
    TEST_ASSERT_EQUAL(1500, mock_delay_arg);
    TEST_ASSERT_EQUAL(1, mock_delay_call);
}

void test_sensor_address_out_of_range(void){
    uint8_t dummy_addr_boundaries[5] = {0x18, 0x28, 0x2E, 0x48, 0x4F};
    uint8_t dummy_addr_out_of_range[7] = {0x17, 0x27, 0x2F, 0x47, 0x50, 0x00, 0xFF};
    for(int i = 0; i < sizeof(dummy_addr_boundaries); i++){
        TEST_ASSERT_FALSE(sensor_address_out_of_range_func(dummy_addr_boundaries[i]));
    }
    for(int i = 0; i < sizeof(dummy_addr_out_of_range); i++){
        TEST_ASSERT_TRUE(sensor_address_out_of_range_func(dummy_addr_out_of_range[i]));
    }
}

void test_channels_out_of_range(void){
     TEST_ASSERT_FALSE(channels_out_of_range_func(FIRST_CHANNEL));
     TEST_ASSERT_FALSE(channels_out_of_range_func(SECOND_CHANNEL));
     TEST_ASSERT_FALSE(channels_out_of_range_func(BOTH_CHANNELS));
     TEST_ASSERT_TRUE(channels_out_of_range_func(0));
     TEST_ASSERT_TRUE(channels_out_of_range_func(4));
}

void test_fail(void){
    char msg[500];
    uint8_t x = 0;
    sprintf(msg, "Test: %x\n", x);
    // TEST_FAIL_MESSAGE(msg);
}