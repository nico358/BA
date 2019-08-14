#include "unity.h"
#include "src/adapter_PAC1720/adapter_PAC1720.h"
#include <stdio.h>

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

uint8_t readNak_call_global = 0;

/** Field- Bus communication spies */
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
    if(readNak_call_global == 0){
        readNak_call_global++;
        return 0x1;
    } 
    mock_i2c_readNak_call++;
    readNak_call_global++;
    TEST_ASSERT_MESSAGE( 1 , "a isn't 2, end of the world!");
    return CONFIG_STANDBY;
}

/* External delay function spy */
void mock_user_delay(uint32_t period){
    mock_delay_arg = period;
    mock_delay_call++;
}

/** Field- Bus communication struct from external */
struct FIELD_BUS_INTERFACE dummy_i2c = {
    .stop       = &mock_i2c_stop,
    .start      = &mock_i2c_start,
    .repStart   = &mock_i2c_rep_start,
    .startWait  = &mock_i2c_start_wait,
    .write      = &mock_i2c_write,
    .readAck    = &mock_i2c_readAck,
    .readNak    = &mock_i2c_readNak
};

struct PAC1720_device test_dev = 
{
    /* Optional name for the device */
	.DEV_name_opt                                           = "TEST_DEV",
    /* Bus address */
	.DEV_sensor_address                                     = 0x18,
    /* Global sensor configuration */
    .DEV_configuration_reg                                  = CONFIG_ALL_CH_ENABLED,
    /* Conversion rate of sensor */
	.DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
    /* One shot register of sensor */
	.DEV_one_shot_reg                                       = ONE_SHOT_DEFAULT,
    /* Channel mask register of sensor*/
    .DEV_mask_reg                                           = MASK_ALL_CH_ALERT_ASSERT,

    /* Optional name for channel one */
    .DEV_CH1_conf.CH_name_opt                               = "TEST_CH1",
    /* Resistance of sense resistor at channel one */
    .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.01f,
    /* Sampling time of current sense for channel one */
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
    /* Current sense sample averaging of channel one */
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    /* Full scale voltage range for current sensing */
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_80mV,
    /* High limit of current for channel one */
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
    /* Low limit of current for channel one */
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    /* Sampling time of source voltage sense */
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    /* Source voltage sample averaging of channel one */
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    /* Source voltage high limit for channel one */
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
    /* Source voltage low limit for channel one */
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,

    /* Optional name for channel two */
    // .DEV_CH2_conf.CH_name_opt                               = "TEST_CH2",
    /* Resistance of sense resistor at channel two */
    .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.01f,
    /* Sampling time of current sense for channel two*/
    .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
    /* Current sense sample averaging of channel two */
    .DEV_CH2_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    /* Full scale voltage range for current sensing */
    .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_80mV,
    /* High limit of current for channel two */
    .DEV_CH2_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
    /* Low limit of current for channel two */
	.DEV_CH2_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    /* Sampling time of source voltage sense */
    .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    /* Source voltage sample averaging of channel two */
    .DEV_CH2_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    /* Source voltage high limit for channel two */
    .DEV_CH2_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
    /* Source voltage low limit for channel two */
	.DEV_CH2_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
};

void setUp(void) {
    TEST_ASSERT_MESSAGE("a isn't 2, end of the world!");
    adapter_init_peripherals(&dummy_i2c, &mock_user_delay);
}

void tearDown(void) {
    mock_i2c_start_call = 0;
    mock_i2c_start_arg = 0;
    mock_i2c_start_wait_call = 0;
    mock_i2c_start_wait_arg = 0;
    mock_i2c_rep_start_call = 0;
    mock_i2c_rep_start_arg = 0;
    mock_i2c_stop_call = 0;
    mock_i2c_write_call = 0;
    mock_i2c_write_arg = 0;
    mock_i2c_readAck_call = 0;
    mock_i2c_readNak_call = 0;

    mock_delay_arg = 0;
    mock_delay_call = 0;
}

void test_driver_initialize_fail(void){
    TEST_ASSERT_EQUAL(PAC1720_INIT_ERROR, adapter_init_PAC1720_user_defined(&test_dev));  
}


void test_driver_initialize(void){
    TEST_ASSERT_EQUAL(PAC1720_OK, adapter_init_PAC1720_user_defined(&test_dev));  

    TEST_ASSERT_EQUAL(6, mock_i2c_start_wait_call);
    TEST_ASSERT_EQUAL(22, mock_i2c_write_call);
    TEST_ASSERT_EQUAL(6, mock_i2c_stop_call);
    TEST_ASSERT_EQUAL(2, mock_i2c_rep_start_call);
    TEST_ASSERT_EQUAL(2, mock_i2c_readAck_call);
    TEST_ASSERT_EQUAL(2, mock_i2c_readNak_call);



    // set_sensor_to_sleep
    // Start Wait: 0x18
    // Write: configuration_register_address
    // Write: CONFIG_STANDBY
    // Stop 

    // sensor_is_in_sleep
    // start wait: 0x18
    // Write: configuration_register_address
    // RepStart: 0x18
    // 1x readNak: CONFIG_STANDBY else PAC1720_INIT_ERROR
    // stop

    // write_all_settings_to_sensor:
    // write_out_global_config_registers
    // Start Wait: 0x18
    // Write: configuration_register_address
    // 4x  Write: tmp_config_reg[4]
    // Stop 

    // write_out_sampling_config_registers
    // Start Wait: 0x18
    // Write: v_source_sampling_configuration_register_address
    // 3x  Write: tmp_smpl_conf_reg[3]
    // Stop 

    // write_out_limit_registers
    // Start Wait: 0x18
    // Write: ch1_sense_voltage_high_limit_register_address
    // 8x  Write: tmp_lmt_reg[8]
    // Stop 

    // readin_sensor_infos_registers
    // start wait: 0x18
    // Write: product_id_register_address
    // RepStart: 0x18
    // 2x readAck:  uint8_t tmp_read[3] = {0};
    // 1x readNak:  uint8_t tmp_read[3] = {0};
    // stop

}