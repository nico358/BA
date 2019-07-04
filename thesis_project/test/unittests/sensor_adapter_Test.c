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

/** Field- Bus communication spies */
unsigned char mock_i2c_start(unsigned char address){
    mock_i2c_start_call++;
    mock_i2c_start_arg = address;
    /** Return fail for 0x18 addr */
    if(address == (0x18 << BUS_ADDRESS_SHIFT) + I2C_WRITE) 
    {
        return 1;
    }
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

/** Provide function pointers */
typedef int8_t      (*adapter_fbus_write)           (const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);
typedef int8_t      (*adapter_fbus_read)            (const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);
typedef void        (*adapter_delay)                (uint32_t period);
typedef bool        (*sensor_address_out_of_range)  (const uint8_t address);
//NULL
typedef uint8_t     (*poll_fbus)                    (uint8_t *addresses, struct FIELD_BUS_INTERFACE *fieldbus_interface, uint8_t loop_var);
typedef void        (*set_fieldbus_ptr)             (struct FIELD_BUS_INTERFACE *external_fieldbus_interface);
typedef void        (*set_delay_ptr)                (delay_function_ptr external_delay);
typedef bool        (*check_mandatory_dev_settings) (struct PAC1720_device *dev_ptr);
typedef bool        (*check_peripherals_initialized)(void);
typedef int8_t      (*fbus_write_loop)              (uint8_t *data_ptr, const uint16_t len);
typedef int8_t      (*fbus_read_loop)               (uint8_t *data_ptr, const uint16_t len);

/** Declare functions */
adapter_fbus_write              adapter_fbus_write_func;
adapter_fbus_read               adapter_fbus_read_func;
adapter_delay                   adapter_delay_func;
sensor_address_out_of_range     sensor_address_out_of_range_func;
//NULL
poll_fbus                       poll_fbus_func;
set_fieldbus_ptr                set_fieldbus_ptr_func;
set_delay_ptr                   set_delay_ptr_func;
check_mandatory_dev_settings    check_mandatory_dev_settings_func;
check_peripherals_initialized   check_peripherals_initialized_func;
fbus_write_loop                 fbus_write_loop_func;
fbus_read_loop                  fbus_read_loop_func;


void setUp(void) {
    // Get function pointers from declaration
    const void* (**test_fptr_field)[]   = (void*) get_ADAPTER_TEST_FPTR_FIELD();
    // Assign function pointers function declares
    adapter_fbus_write_func             = (adapter_fbus_write)              test_fptr_field[0];
    adapter_fbus_read_func              = (adapter_fbus_read)               test_fptr_field[1];
    adapter_delay_func                  = (adapter_delay)                   test_fptr_field[2];
    sensor_address_out_of_range_func    = (sensor_address_out_of_range)     test_fptr_field[3];
    //NULL
    poll_fbus_func                      = (poll_fbus)                       test_fptr_field[5];
    set_fieldbus_ptr_func               = (set_fieldbus_ptr)                test_fptr_field[6];
    set_delay_ptr_func                  = (set_delay_ptr)                   test_fptr_field[7];
    check_mandatory_dev_settings_func   = (check_mandatory_dev_settings)    test_fptr_field[8];
    check_peripherals_initialized_func  = (check_peripherals_initialized)   test_fptr_field[9];
    fbus_write_loop_func                = (fbus_write_loop)                 test_fptr_field[10];
    fbus_read_loop_func                 = (fbus_read_loop)                  test_fptr_field[11];
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

    set_fieldbus_ptr_func(NULL);
    set_delay_ptr_func(NULL);
}

void test_adapter_find_sensors(void){
    /* Set up dummy inputs */
    uint8_t dummy_addresses[16] = {0};
    /** Verify function call */
    uint8_t test_result = SENSOR_ADDRESS_NUMBER -1;
    uint8_t dummy_last_sensor_addr = PAC1720_addresses[SENSOR_ADDRESS_NUMBER -1];
    uint8_t dummy_sensor_addr_return = (dummy_last_sensor_addr << BUS_ADDRESS_SHIFT) + I2C_WRITE;
    TEST_ASSERT_EQUAL(test_result, adapter_find_sensors(dummy_addresses, &dummy_i2c, &mock_user_delay));
    TEST_ASSERT_EQUAL(SENSOR_ADDRESS_NUMBER + max_search_attempts, mock_i2c_start_call);
    TEST_ASSERT_EQUAL(dummy_sensor_addr_return, mock_i2c_start_arg);
    TEST_ASSERT_EQUAL(max_search_attempts +1, mock_delay_call);
    TEST_ASSERT_EQUAL(10, mock_delay_arg);
    TEST_ASSERT_EQUAL(SENSOR_ADDRESS_NUMBER + max_search_attempts, mock_i2c_stop_call);
    uint8_t test_arr[16] = {0};
    /** Copy sensor addresses in test array but first address */
    for(int i = 1; i < SENSOR_ADDRESS_NUMBER; i++){
        test_arr[i] = PAC1720_addresses[i];
    }
    TEST_ASSERT_EQUAL_HEX8_ARRAY(test_arr, dummy_addresses, sizeof(dummy_addresses));
}

void test_poll_fbus(void){
    /* Set up dummy inputs */
    uint8_t dummy_loop_var = 0;
    uint8_t dummy_sensor_addr = PAC1720_addresses[dummy_loop_var];
    uint8_t dummy_sensor_addr_return = (dummy_sensor_addr << BUS_ADDRESS_SHIFT) + I2C_WRITE;
    uint8_t dummy_addresses[2] = {0};
    /** Check return no match */
    TEST_ASSERT_EQUAL(1, poll_fbus_func(dummy_addresses, &dummy_i2c, dummy_loop_var));
    TEST_ASSERT_EQUAL(1, mock_i2c_start_call);
    TEST_ASSERT_EQUAL(dummy_sensor_addr_return, mock_i2c_start_arg);
    TEST_ASSERT_EQUAL(1, mock_i2c_stop_call);
    uint8_t test_arr[2] = {0x00, 0x00};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(test_arr, dummy_addresses, sizeof(dummy_addresses));
    /** Check return match */
    dummy_loop_var = 1;
    dummy_sensor_addr = PAC1720_addresses[dummy_loop_var];
    dummy_sensor_addr_return = (dummy_sensor_addr << BUS_ADDRESS_SHIFT) + I2C_WRITE;
    TEST_ASSERT_EQUAL(0, poll_fbus_func(dummy_addresses, &dummy_i2c, dummy_loop_var));
    TEST_ASSERT_EQUAL(2, mock_i2c_start_call);
    TEST_ASSERT_EQUAL(dummy_sensor_addr_return, mock_i2c_start_arg);
    TEST_ASSERT_EQUAL(2, mock_i2c_stop_call);
    test_arr[1] = dummy_sensor_addr;
    TEST_ASSERT_EQUAL_HEX8_ARRAY(test_arr, dummy_addresses, sizeof(dummy_addresses));
}

void test_fbus_write_loop(void){
    set_fieldbus_ptr_func(&dummy_i2c);
        /* Set up dummy inputs */
    uint8_t dummy_data[2] = {0xAA, 0xBB};
    uint8_t dummy_len = sizeof(dummy_data);
    /* Execute function */
    TEST_ASSERT_EQUAL(PAC1720_OK, fbus_write_loop_func(dummy_data, dummy_len));
    /* Evaluate spy parameters */
    TEST_ASSERT_EQUAL_HEX8(dummy_data[1], mock_i2c_write_arg);
    TEST_ASSERT_EQUAL(dummy_len, mock_i2c_write_call);
}
void test_fbus_read_loop(void){
    set_fieldbus_ptr_func(&dummy_i2c);
        /* Set up dummy inputs */
    uint8_t dummy_data[3] = {0};
    uint8_t dummy_len = sizeof(dummy_data);
    /* Execute function */
    TEST_ASSERT_EQUAL_HEX8(PAC1720_OK, fbus_read_loop_func(dummy_data, dummy_len));
    /* Evaluate spy parameters */
    TEST_ASSERT_EQUAL(2, mock_i2c_readAck_call);
    TEST_ASSERT_EQUAL(1, mock_i2c_readNak_call);
    /* Evaluate array reading */
    uint8_t test_arr[3] = {0xDD, 0xDD, 0xDE};
    TEST_ASSERT_EQUAL_HEX8_ARRAY(test_arr, dummy_data, dummy_len);
}  

void test_check_peripherals_initialized(void){
    TEST_ASSERT_FALSE(check_peripherals_initialized_func());
    set_fieldbus_ptr_func(&dummy_i2c);
    set_delay_ptr_func(&mock_user_delay);
    TEST_ASSERT_TRUE(check_peripherals_initialized_func());
}

void test_adapter_fbus_write(void){
    set_fieldbus_ptr_func(&dummy_i2c);
    /* Set up dummy inputs */
    uint8_t dummy_address = 0x28;
    uint8_t dummy_address_return = (dummy_address << BUS_ADDRESS_SHIFT) + I2C_WRITE;
    uint8_t dummy_reg_address = 0x11;
    uint8_t dummy_data[2] = {0xAA, 0xBB};
    uint8_t dummy_len = sizeof(dummy_data);
    /* Execute function */
    TEST_ASSERT_EQUAL(PAC1720_OK, adapter_fbus_write_func(dummy_address, dummy_reg_address, dummy_data, dummy_len));
    /* Evaluate spy parameters */
    TEST_ASSERT_EQUAL_HEX8(dummy_address_return, mock_i2c_start_wait_arg);
    TEST_ASSERT_EQUAL(1,mock_i2c_start_wait_call);
    TEST_ASSERT_EQUAL_HEX8(dummy_data[1], mock_i2c_write_arg);
    TEST_ASSERT_EQUAL(3, mock_i2c_write_call);
    TEST_ASSERT_EQUAL(1,mock_i2c_stop_call);
}   

void test_adapter_fbus_read(void){
    set_fieldbus_ptr_func(&dummy_i2c);
    /* Set up dummy inputs */
    uint8_t dummy_address = 0x28;
    uint8_t dummy_address_write_return = (dummy_address << BUS_ADDRESS_SHIFT) + I2C_WRITE;
    uint8_t dummy_address_read_return = (dummy_address << BUS_ADDRESS_SHIFT) + I2C_READ;
    uint8_t dummy_reg_address = 0x11;
    uint8_t dummy_data[3] = {0};
    uint8_t dummy_len = sizeof(dummy_data);
    /* Execute function */
    TEST_ASSERT_EQUAL_HEX8(PAC1720_OK, adapter_fbus_read_func(dummy_address, dummy_reg_address, dummy_data, dummy_len));
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
    set_delay_ptr_func(&mock_user_delay);
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

void test_check_mandatory_dev_settings(void){
    static struct PAC1720_device dummy_dev;
    dummy_dev.DEV_sensor_address = 0x18;
    TEST_ASSERT_FALSE(check_mandatory_dev_settings_func(&dummy_dev));
    dummy_dev.DEV_CH1_conf.CH_current_sense_resistor_value = 0.8f;
    TEST_ASSERT_FALSE(check_mandatory_dev_settings_func(&dummy_dev));
    dummy_dev.DEV_CH2_conf.CH_current_sense_resistor_value = 0.8f;
    TEST_ASSERT_TRUE(check_mandatory_dev_settings_func(&dummy_dev));
}

void test_fail(void){
    // struct PAC1720_device dev;
    // char msg[500];
    // sprintf(msg, "Test: %d", cnt);
    // TEST_FAIL_MESSAGE(msg);
}