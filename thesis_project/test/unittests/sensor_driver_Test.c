#include "unity.h"
#include "lib/PAC1720_driver/PAC1720_driver.h"

/** Provide function definitions like in declaration */
typedef int8_t (*calculate_BUS_CURRENT) (const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings);
typedef float (*calculate_SENSED_VOLTAGE) (const uint16_t *v_sense_voltage_reg_ptr, const uint8_t *current_sense_sampling_time_reg_ptr);
typedef int8_t (*calculate_FSC) (struct PAC1720_channel_config *config_ptr);
typedef uint16_t (*twos_complement) (const uint16_t *complement);
typedef bool (*is_negative_value) (const uint16_t *value);
typedef uint16_t (*right_bit_shift) (const uint16_t *doublebyte, uint8_t shift);
typedef int8_t (*device_null_pointer_check) (const struct PAC1720_device *device_ptr);
typedef int8_t (*calculate_BUS_VOLTAGE) (const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings);
typedef float (*calculate_SOURCE_VOLTAGE) (const uint16_t *v_source_voltage_reg_ptr, const uint8_t *source_voltage_sampling_time_reg_ptr);
typedef int8_t (*calculate_FSV) (struct PAC1720_channel_config *config_ptr);
typedef int8_t (*calculate_BUS_POWER) (const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings);
typedef int8_t (*calculate_FSP) (struct PAC1720_channel_config *config_ptr);

/** Declare instances */
calculate_BUS_CURRENT calculate_BUS_CURRENT_func;
calculate_SENSED_VOLTAGE calculate_SENSED_VOLTAGE_func;
calculate_FSC calculate_FSC_func;
twos_complement twos_complement_func;
is_negative_value is_negative_value_func;
right_bit_shift right_bit_shift_func;
device_null_pointer_check device_null_pointer_check_func;
calculate_BUS_VOLTAGE calculate_BUS_VOLTAGE_func;
calculate_SOURCE_VOLTAGE calculate_SOURCE_VOLTAGE_func;
calculate_FSV calculate_FSV_func;
calculate_BUS_POWER calculate_BUS_POWER_func;
calculate_FSP calculate_FSP_func;

struct PAC1720_device dev;

void dummy_func(void){}

void setUp(void) {
    // Get function pointers from declaration
    const (**test_fptr_field)[]         = (PAC1720_fptr*) get_TEST_FPTR_FIELD();
    // Assign function pointers to instances
    calculate_BUS_CURRENT_func          = (calculate_BUS_CURRENT) test_fptr_field[0];
    calculate_SENSED_VOLTAGE_func       = (calculate_SENSED_VOLTAGE) test_fptr_field[1];
    calculate_FSC_func                  = (calculate_FSC) test_fptr_field[2];
    twos_complement_func                = (twos_complement) test_fptr_field[3];
    is_negative_value_func              = (is_negative_value) test_fptr_field[4];
    right_bit_shift_func                = (right_bit_shift) test_fptr_field[5];
    device_null_pointer_check_func      = (device_null_pointer_check) test_fptr_field[6];
    calculate_BUS_VOLTAGE_func          = (calculate_BUS_VOLTAGE) test_fptr_field[7];
    calculate_SOURCE_VOLTAGE_func       = (calculate_SOURCE_VOLTAGE) test_fptr_field[8];
    calculate_FSV_func                  = (calculate_FSV) test_fptr_field[9];
    calculate_BUS_POWER_func            = (calculate_BUS_POWER) test_fptr_field[10];
    calculate_FSP_func                  = (calculate_FSP) test_fptr_field[11];
}

void tearDown(void) {
    
}

void test_calculate_BUS_CURRENT (void){
    // Setup input values
    dev.ch1_readings.v_sense_voltage_reg = 0b0110100110000000;
    dev.sensor_config_ch1.current_sense_sampling_time_reg = 0x05;
    // Test reading done flag is false
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_BUS_CURRENT_func(&dev.sensor_config_ch1, &dev.ch1_readings));
    dev.ch1_readings.reading_done = true;
    // Test FSC not set
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_BUS_CURRENT_func(&dev.sensor_config_ch1, &dev.ch1_readings));
    dev.sensor_config_ch1.current_sense_FSC = 2.0f;
    // Test correct current- calculation- denominator selection
    TEST_ASSERT_EQUAL_FLOAT(2047.0f, DENOMINATOR_values_current_sense[dev.sensor_config_ch1.current_sense_sampling_time_reg]);
    // Test correct current calculation
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_BUS_CURRENT_func(&dev.sensor_config_ch1, &dev.ch1_readings));
    TEST_ASSERT_EQUAL_FLOAT(1.64924276f, dev.ch1_readings.res_CURRENT);
    // Reset flag for next tests
    dev.ch1_readings.reading_done = false;
}

void test_calculate_BUS_VOLTAGE(void){
    // Setup input values
    dev.ch1_readings.v_source_voltage_reg = 0b1001100110000000;
    dev.sensor_config_ch1.source_voltage_sampling_time_reg = 0x02;
    dev.sensor_config_ch1.source_voltage_FSV = 39.96f;
    // Test reading flag not set
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_BUS_VOLTAGE_func(&dev.sensor_config_ch1, &dev.ch1_readings));
    dev.ch1_readings.reading_done = true;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_BUS_VOLTAGE_func(&dev.sensor_config_ch1, &dev.ch1_readings));
    TEST_ASSERT_EQUAL_FLOAT(23.9838123f, dev.ch1_readings.res_SOURCE_VOLTAGE);
    // Reset flag for next tests
    dev.ch1_readings.reading_done = false;
}

void test_calculate_BUS_POWER(void){
    // Test reading done flag not set
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_BUS_POWER_func(&dev.sensor_config_ch1, &dev.ch1_readings));
    dev.ch1_readings.reading_done = true;
    // Test FSP = 0
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_BUS_POWER_func(&dev.sensor_config_ch1, &dev.ch1_readings));
    // Setup input values
    dev.sensor_config_ch1.power_sense_FSP = 79.92f;
    dev.ch1_readings.power_ratio_reg = 0b0011100001000111;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_BUS_POWER_func(&dev.sensor_config_ch1, &dev.ch1_readings));
    TEST_ASSERT_EQUAL_FLOAT(17.5693493f, dev.ch1_readings.res_POWER);
    // Reset value
    dev.sensor_config_ch1.power_sense_FSP = 0;
}

void test_calculate_SENSED_VOLTAGE (void){
    // Set sampling time to allow determination of resolution
    dev.sensor_config_ch1.current_sense_sampling_time_reg = 0x05;
    // Test negative voltage return value
    dev.ch1_readings.v_sense_voltage_reg = 0b1001011010000000;
    TEST_ASSERT_EQUAL_FLOAT(-1688.0f, calculate_SENSED_VOLTAGE_func(&dev.ch1_readings.v_sense_voltage_reg, &dev.sensor_config_ch1.current_sense_sampling_time_reg));
    // Test positive voltage return value
    dev.ch1_readings.v_sense_voltage_reg = 0b0110100110000000;
    TEST_ASSERT_EQUAL_FLOAT(1688.0f, calculate_SENSED_VOLTAGE_func(&dev.ch1_readings.v_sense_voltage_reg, &dev.sensor_config_ch1.current_sense_sampling_time_reg));
    // Reset value
    dev.sensor_config_ch1.source_voltage_sampling_time_reg = 0;
}

void test_calculate_SOURCE_VOLTAGE(void){
    // Test source voltage return value with sample time 2.5 ms (sample reg = 0x00)
    dev.ch1_readings.v_source_voltage_reg = 0b1111111100000000;
    TEST_ASSERT_EQUAL_FLOAT(255.0f, calculate_SOURCE_VOLTAGE_func(&dev.ch1_readings.v_source_voltage_reg, &dev.sensor_config_ch1.source_voltage_sampling_time_reg));
     // Set sampling time to allow shifting in correct resolution (11bit here)
    dev.sensor_config_ch1.source_voltage_sampling_time_reg = 0x03;
    // Test source voltage return value
    dev.ch1_readings.v_source_voltage_reg = 0b0100010000100000;
    TEST_ASSERT_EQUAL_FLOAT(545.0f, calculate_SOURCE_VOLTAGE_func(&dev.ch1_readings.v_source_voltage_reg, &dev.sensor_config_ch1.source_voltage_sampling_time_reg));
    // Set sampling time to allow shifting in correct resolution (10bit here)
    dev.sensor_config_ch1.source_voltage_sampling_time_reg = 0x02;
    // Test source voltage return value
    dev.ch1_readings.v_source_voltage_reg = 0b1001100110000000;
    TEST_ASSERT_EQUAL_FLOAT(614.0f, calculate_SOURCE_VOLTAGE_func(&dev.ch1_readings.v_source_voltage_reg, &dev.sensor_config_ch1.source_voltage_sampling_time_reg));
}

void test_calculate_FSC (void){
    // Test correct FSR selection, reg=0 => select first value
    TEST_ASSERT_EQUAL_FLOAT(0.01f, FSR_values[dev.sensor_config_ch1.current_sense_FSR_reg ]);
    // Test resistor value not set
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSC_func(&dev.sensor_config_ch1));
    // Test correct FSC calculation
    dev.sensor_config_ch1.current_sense_FSR_reg = 0x01;
    dev.sensor_config_ch1.current_sense_resistor_value = 0.01f;
    calculate_FSC_func(&dev.sensor_config_ch1);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, dev.sensor_config_ch1.current_sense_FSC);
    // Reset value
    dev.sensor_config_ch1.current_sense_FSC = 0;
}

void test_calculate_FSV(void){
    // Set sampling time to allow shifting in correct resolution (10bit here)
    dev.sensor_config_ch1.source_voltage_sampling_time_reg = 0x02;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_FSV_func(&dev.sensor_config_ch1));
    TEST_ASSERT_EQUAL_FLOAT(39.9609375, dev.sensor_config_ch1.source_voltage_FSV);
    // Reset value
    dev.sensor_config_ch1.source_voltage_FSV = 0;
}

void test_calculate_FSP(void){
    // Test FSC is zero
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSP_func(&dev.sensor_config_ch1));
    // Set FSC
    dev.sensor_config_ch1.current_sense_FSC = 2.0f;
    // Test FSV is zero
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSP_func(&dev.sensor_config_ch1));
    // Set FSV and validate FSP
    dev.sensor_config_ch1.source_voltage_FSV = 39.96f;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_FSP_func(&dev.sensor_config_ch1));
    TEST_ASSERT_EQUAL_FLOAT(79.92f, dev.sensor_config_ch1.power_sense_FSP);
}

void test_twos_complement (void){
    uint16_t int_to_test = 0x0F0A;
    TEST_ASSERT_EQUAL_UINT16(0xF0F6, twos_complement_func(&int_to_test));
}

void test_is_negative_value (void){
    uint16_t int_to_test = 0x7FFF;
    TEST_ASSERT_FALSE(is_negative_value_func(&int_to_test));
    int_to_test = 0x8000;
    TEST_ASSERT_TRUE(is_negative_value_func(&int_to_test));
}

void test_right_bit_shift(void) {
    uint16_t int_to_shift = 0x8000;
    TEST_ASSERT_EQUAL_UINT16(0x01, right_bit_shift_func(&int_to_shift, 15));
}

void test_device_null_pointer_check(void) {
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, device_null_pointer_check_func((void*)0));
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, device_null_pointer_check_func(&dev));
    dev.write = &dummy_func;
    dev.read = &dummy_func;
    dev.delay_ms = &dummy_func;
    TEST_ASSERT_EQUAL(PAC1720_OK, device_null_pointer_check_func(&dev));
}
