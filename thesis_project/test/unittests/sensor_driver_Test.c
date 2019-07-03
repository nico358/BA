#include "unity.h"
#include "lib/PAC1720_driver/PAC1720_driver.h"
// #include "lib/PAC1720_driver/MockPAC1720_driver.h"

struct 	PAC1720_internal
{
    /*! Bus read function pointer */
	PAC1720_fptr read;
	/*! Bus write function pointer */
	PAC1720_fptr write;
	/*! Delay function pointer */
	delay_fptr 	 delay_ms;

    /* Sensor product id */
	uint8_t      sensor_product_id;
	/* Sensor manufacturer id */
	uint8_t      sensor_manufact_id;
	/* Sensor revision */
	uint8_t      sensor_revision;
};

struct PAC1720_ch_internal
{
    /*! Full Scale Current (FSC) */
	float 		current_sense_FSC;
    /*! Full Scale Voltage (FSV) */
	float 		source_voltage_FSV;
	/*! Full Scale Power (FSP)  */
	float 		power_sense_FSP;
};

struct 	PAC1720_meas_internal
{
    /* Current sense voltage register */
    uint16_t    v_source_voltage_reg;
    /* Source voltage sense register */
    uint16_t    v_sense_voltage_reg;
    /* Power ratio register */
    uint16_t    power_ratio_reg; 
};

/** Helper function definitions */
void dummy_func(void);
int8_t spy_i2c_write_read(uint8_t address, uint8_t reg_address, uint8_t *data, uint8_t len);

/** Provide function definitions like in declaration */
typedef int8_t                          (*calculate_BUS_CURRENT)            (const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);
typedef float                           (*calculate_SENSED_VOLTAGE)         (const uint16_t *v_sense_voltage_reg_ptr, const uint8_t *current_sense_sampling_time_reg_ptr);
typedef int8_t                          (*calculate_FSC)                    (struct PAC1720_CH_config *config_ptr);
typedef uint16_t                        (*twos_complement)                  (const uint16_t *complement);
typedef bool                            (*is_negative_value)                (const uint16_t *value);
typedef uint16_t                        (*right_bit_shift)                  (const uint16_t *doublebyte, uint8_t shift);
typedef int8_t                          (*device_null_pointer_check)        (const struct PAC1720_device *device_ptr); 
typedef int8_t                          (*calculate_BUS_VOLTAGE)            (const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);
typedef float                           (*calculate_SOURCE_VOLTAGE)         (const uint16_t *v_source_voltage_reg_ptr, const uint8_t *source_voltage_sampling_time_reg_ptr);
typedef int8_t                          (*calculate_FSV)                    (struct PAC1720_CH_config *config_ptr);
typedef int8_t                          (*calculate_BUS_POWER)              (const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);
typedef int8_t                          (*calculate_FSP)                    (struct PAC1720_ch_internal *ch_internal_ptr); 
typedef int8_t                          (*read_registers)                   (const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len);
typedef int8_t                          (*write_registers)                  (const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len);
typedef void                            (*assign_ch_limit_registers)        (struct PAC1720_device *device_ptr, uint8_t tmp_lmt_reg[8]);///////////////
typedef void                            (*assign_internal_measurements_registers) (struct PAC1720_device *device_ptr, uint8_t tmp_meas_reg[12]);//////////////
typedef uint16_t                        (*combine_bytes)                    (const uint8_t *lsb, const uint8_t *msb);
typedef void                            (*assign_sampling_config_registers) (struct PAC1720_device *device_ptr, uint8_t tmp_smpl_conf_reg[3]);////////
typedef void                            (*assign_limit_status_registers)    (struct PAC1720_device *device_ptr, uint8_t tmp_limit_reg[2]);/////////////
typedef struct PAC1720_internal *       (*create_internal_ptr)              (const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay);
typedef struct PAC1720_ch_internal *    (*create_ch_internal_ptr)           (void);
typedef void                            (*destroy_internal_ptr)             (struct PAC1720_internal *internal);
typedef void                            (*destroy_ch_internal_ptr)          (struct PAC1720_ch_internal *ch_internal);
typedef int8_t                          (*peripherals_null_pointer_check)   (const PAC1720_fptr write, const PAC1720_fptr read, const delay_fptr delay);
typedef struct PAC1720_meas_internal *  (*create_meas_internal_ptr)         (void);
typedef void                            (*destroy_meas_internal_ptr)        (struct PAC1720_meas_internal *meas_internal);
typedef void                            (*set_measurements_zero)            (struct PAC1720_device *device_ptr);////////
typedef void                            (*assign_tmp_sampling_config_array) (struct PAC1720_device *device_ptr, uint8_t tmp_smpl_conf_reg[3]);////////
typedef void                            (*assign_tmp_limit_array)           (struct PAC1720_device *device_ptr, uint8_t tmp_lmt_reg[8]);///////////



/** Declare function instances */
calculate_BUS_CURRENT                   calculate_BUS_CURRENT_func;
calculate_SENSED_VOLTAGE                calculate_SENSED_VOLTAGE_func;
calculate_FSC                           calculate_FSC_func;
twos_complement                         twos_complement_func;
is_negative_value                       is_negative_value_func;
right_bit_shift                         right_bit_shift_func;
device_null_pointer_check               device_null_pointer_check_func;
calculate_BUS_VOLTAGE                   calculate_BUS_VOLTAGE_func;
calculate_SOURCE_VOLTAGE                calculate_SOURCE_VOLTAGE_func;
calculate_FSV                           calculate_FSV_func;
calculate_BUS_POWER                     calculate_BUS_POWER_func;
calculate_FSP                           calculate_FSP_func;
read_registers                          read_registers_func;
write_registers                         write_registers_func;
assign_ch_limit_registers               assign_ch_limit_registers_func;//////////////
assign_internal_measurements_registers  assign_internal_measurements_registers_func;///////////
combine_bytes                           combine_bytes_func;
assign_sampling_config_registers        assign_sampling_config_registers_func;///////////////
assign_limit_status_registers           assign_limit_status_registers_func;////////////   
create_internal_ptr                     create_internal_ptr_func; 
create_ch_internal_ptr                  create_ch_internal_ptr_func;
destroy_internal_ptr                    destroy_internal_ptr_func;
destroy_ch_internal_ptr                 destroy_ch_internal_ptr_func;  
peripherals_null_pointer_check          peripherals_null_pointer_check_func;
create_meas_internal_ptr                create_meas_internal_ptr_func;
destroy_meas_internal_ptr               destroy_meas_internal_ptr_func;
set_measurements_zero                   set_measurements_zero_func;//////////////////
assign_tmp_sampling_config_array        assign_tmp_sampling_config_array_func;//////////
assign_tmp_limit_array                  assign_tmp_limit_array_func;//////////             

/* Unity stuff */
void setUp(void) {
    // Get function pointers from declaration
    const void* (**test_fptr_field)[]   = (void*) get_TEST_DRIVER_FPTR_FIELD();
    // Assign function pointers to instances
    calculate_BUS_CURRENT_func          = (calculate_BUS_CURRENT)               test_fptr_field[0];
    calculate_SENSED_VOLTAGE_func       = (calculate_SENSED_VOLTAGE)            test_fptr_field[1];
    calculate_FSC_func                  = (calculate_FSC)                       test_fptr_field[2];
    twos_complement_func                = (twos_complement)                     test_fptr_field[3];
    is_negative_value_func              = (is_negative_value)                   test_fptr_field[4];
    right_bit_shift_func                = (right_bit_shift)                     test_fptr_field[5];
    device_null_pointer_check_func      = (device_null_pointer_check)           test_fptr_field[6];
    calculate_BUS_VOLTAGE_func          = (calculate_BUS_VOLTAGE)               test_fptr_field[7];
    calculate_SOURCE_VOLTAGE_func       = (calculate_SOURCE_VOLTAGE)            test_fptr_field[8];
    calculate_FSV_func                  = (calculate_FSV)                       test_fptr_field[9];
    calculate_BUS_POWER_func            = (calculate_BUS_POWER)                 test_fptr_field[10];
    calculate_FSP_func                  = (calculate_FSP)                       test_fptr_field[11];
    read_registers_func                 = (read_registers)                      test_fptr_field[12];
    write_registers_func                = (write_registers)                     test_fptr_field[13];
    assign_ch_limit_registers_func      = (assign_ch_limit_registers)           test_fptr_field[14];//////////////
    assign_internal_measurements_registers_func = (assign_internal_measurements_registers) test_fptr_field[15];/////////////
    combine_bytes_func                  = (combine_bytes)                       test_fptr_field[16];
    assign_sampling_config_registers_func = (assign_sampling_config_registers)  test_fptr_field[17];///////////////
    assign_limit_status_registers_func  = (assign_limit_status_registers)       test_fptr_field[18];////////////
    create_internal_ptr_func            = (create_internal_ptr)                 test_fptr_field[19];
    create_ch_internal_ptr_func         = (create_ch_internal_ptr)              test_fptr_field[20];
    destroy_internal_ptr_func           = (destroy_internal_ptr)                test_fptr_field[21];
    destroy_ch_internal_ptr_func        = (destroy_ch_internal_ptr)             test_fptr_field[22];
    peripherals_null_pointer_check_func = (peripherals_null_pointer_check)      test_fptr_field[23];
    create_meas_internal_ptr_func       = (create_meas_internal_ptr)            test_fptr_field[24];
    destroy_meas_internal_ptr_func      = (destroy_meas_internal_ptr)           test_fptr_field[25];
    set_measurements_zero_func          = (set_measurements_zero)               test_fptr_field[26];/////////
    assign_tmp_sampling_config_array_func = (assign_tmp_sampling_config_array)  test_fptr_field[27];//////////
    assign_tmp_limit_array_func         = (assign_tmp_limit_array)              test_fptr_field[28];///////
}

void tearDown(void) {}


// Test null_pointer_check with dummy pointer
void dummy_func(void){}

// Test spy for i2c interface
int8_t spy_i2c_write_read(uint8_t address, uint8_t reg_address, uint8_t *data, uint8_t len){
    // Push function arguments into data pointer
    *data = address;
    data++;
    *data = reg_address;
    data++;
    *data = len;
    return PAC1720_OK;
}

void test_create_meas_internal_ptr(void){
    struct PAC1720_meas_internal * test_ptr = create_meas_internal_ptr_func();
    TEST_ASSERT_FALSE(test_ptr == NULL);
    TEST_ASSERT_EQUAL(sizeof(struct PAC1720_meas_internal), sizeof(*test_ptr));
    TEST_ASSERT_EQUAL(0, test_ptr->power_ratio_reg);
    TEST_ASSERT_EQUAL(0, test_ptr->v_sense_voltage_reg);
    TEST_ASSERT_EQUAL(0, test_ptr->v_source_voltage_reg);
    free(test_ptr);
}

void test_create_ch_internal_ptr(void){
    struct PAC1720_ch_internal * test_ptr = create_ch_internal_ptr_func();
    TEST_ASSERT_FALSE(test_ptr == NULL);
    TEST_ASSERT_EQUAL(sizeof(struct PAC1720_ch_internal), sizeof(*test_ptr));
    TEST_ASSERT_EQUAL(0, test_ptr->current_sense_FSC);
    TEST_ASSERT_EQUAL(0, test_ptr->power_sense_FSP);
    TEST_ASSERT_EQUAL(0, test_ptr->source_voltage_FSV);
    free(test_ptr);
}

void test_create_internal_ptr(void){
    PAC1720_fptr dummy_write = (PAC1720_fptr) &dummy_func;
    PAC1720_fptr dummy_read = (PAC1720_fptr) &dummy_func;
    delay_fptr dummy_delay = (delay_fptr) &dummy_func;
    struct PAC1720_internal * test_ptr = create_internal_ptr_func(dummy_write, dummy_read, dummy_delay);
    TEST_ASSERT_FALSE(test_ptr == NULL);
    TEST_ASSERT_EQUAL(sizeof(struct PAC1720_internal), sizeof(*test_ptr));
    TEST_ASSERT_EQUAL_PTR(&dummy_func, test_ptr->write);
    TEST_ASSERT_EQUAL_PTR(&dummy_func, test_ptr->read);
    TEST_ASSERT_EQUAL_PTR(&dummy_func, test_ptr->delay_ms);
    TEST_ASSERT_EQUAL(0, test_ptr->sensor_product_id);
    TEST_ASSERT_EQUAL(0, test_ptr->sensor_manufact_id);
    TEST_ASSERT_EQUAL(0, test_ptr->sensor_revision);
    free(test_ptr);
}

void test_read_registers(void){
    // Declare test structs
    static struct PAC1720_device dummy_dev;
    static struct PAC1720_internal dummy_internal;
    dummy_dev.internal = &dummy_internal;
    // Assign spy 
    dummy_internal.read = (PAC1720_fptr) &spy_i2c_write_read;
    // Set function arguments
    dummy_dev.DEV_sensor_address = 0xF0;
    uint8_t data[3] = {0};
    uint8_t reg_addr = 0x11;
    uint8_t len = 3;
    // Call function to test
    TEST_ASSERT_EQUAL(PAC1720_OK, read_registers_func(&dummy_dev, reg_addr, data, len));
    // Verify values
    TEST_ASSERT_EQUAL(dummy_dev.DEV_sensor_address, data[0]);
    TEST_ASSERT_EQUAL(reg_addr, data[1]);
    TEST_ASSERT_EQUAL(len, data[2]);
}

void test_write_registers(void){
    // Declare test structs
    static struct PAC1720_device dummy_dev;
    static struct PAC1720_internal dummy_internal;
    dummy_dev.internal = &dummy_internal;
    // Assign spy
    dummy_internal.write = (PAC1720_fptr) &spy_i2c_write_read;
    // Set function arguments
    dummy_dev.DEV_sensor_address = 0xF0;
    uint8_t data[3] = {0};
    uint8_t reg_addr = 0x11;
    uint8_t len = 3;
    // Call function to test
    TEST_ASSERT_EQUAL(PAC1720_OK, write_registers_func(&dummy_dev, reg_addr, data, len));
    // Verify values
    TEST_ASSERT_EQUAL(dummy_dev.DEV_sensor_address, data[0]);
    TEST_ASSERT_EQUAL(reg_addr, data[1]);
    TEST_ASSERT_EQUAL(len, data[2]);
}

void test_assign_tmp_limit_array(void){

}

void test_assign_tmp_sampling_config_array(void){

}

void test_set_measurements_zero(void){

}

void test_assign_ch_limit_registers(void){

}

void test_assign_internal_measurements_registers(void){

}

void test_assign_sampling_config_registers(void){

}

void test_assign_limit_status_registers(void){

}


// void test_cut_up_limit_registers(void){
//     // Declare test- device struct
//     static struct PAC1720_device dev;
//     // Setup dummy values
//     uint8_t high_lim_dummy_fail = 0b00000000;
//     dev.high_limit_status_reg = high_lim_dummy_fail;
//     cut_up_limit_registers_func(&dev);
//     TEST_ASSERT_FALSE(dev.conversion_cycle_complete);
//     uint8_t high_lim_dummy_success = 0b10000000;
//     dev.high_limit_status_reg = high_lim_dummy_success;
//     cut_up_limit_registers_func(&dev);
//     TEST_ASSERT_TRUE(dev.conversion_cycle_complete);
// }

// void test_cut_up_sampling_registers(void){
//     // Declare test- device struct
//     static struct PAC1720_device dev;
//     // Setup dummy values
//     uint8_t dummy_Vsource_reg = 0b11011000;
//     uint8_t dummy_Vsense_reg  = 0b11011001;
//     dev.source_voltage_sampling_config_reg = dummy_Vsource_reg;
//     dev.ch1_current_sense_sampling_config_reg = dummy_Vsense_reg;
//     dev.ch2_current_sense_sampling_config_reg = dummy_Vsense_reg;
//     // Verify function
//     cut_up_sampling_registers_func(&dev);
//     TEST_ASSERT_EQUAL(0b00000011, dev.sensor_config_ch2.source_voltage_sampling_time_reg);
//     TEST_ASSERT_EQUAL(0b00000001, dev.sensor_config_ch2.source_voltage_sampling_average_reg);
//     TEST_ASSERT_EQUAL(0b00000010, dev.sensor_config_ch1.source_voltage_sampling_time_reg);
//     TEST_ASSERT_EQUAL(0b00000000, dev.sensor_config_ch1.source_voltage_sampling_average_reg);

//     TEST_ASSERT_EQUAL(0b00000101, dev.sensor_config_ch1.current_sense_sampling_time_reg);
//     TEST_ASSERT_EQUAL(0b00000010, dev.sensor_config_ch1.current_sense_sampling_average_reg);
//     TEST_ASSERT_EQUAL(0b00000001, dev.sensor_config_ch1.current_sense_FSR_reg);
    
//     TEST_ASSERT_EQUAL(0b00000101, dev.sensor_config_ch2.current_sense_sampling_time_reg);
//     TEST_ASSERT_EQUAL(0b00000010, dev.sensor_config_ch2.current_sense_sampling_average_reg);
//     TEST_ASSERT_EQUAL(0b00000001, dev.sensor_config_ch2.current_sense_FSR_reg);
// }

// void test_assign_config_register_values(void){
//     // Declare test- device struct
//     static struct PAC1720_device dev;
//     uint8_t test_reg_field[32];
//     // Fill test array
//     for(int i = 0; i < 32; i++){
//         test_reg_field[i] = i;
//     }
//     // Verify assignment function
//     assign_config_register_values_func(&dev, test_reg_field);
//     TEST_ASSERT_EQUAL(test_reg_field[0], dev.configuration_reg); 
//     TEST_ASSERT_EQUAL(test_reg_field[1], dev.conversion_rate_reg);   
//     TEST_ASSERT_EQUAL(test_reg_field[2], dev.one_shot_reg);                              
//     TEST_ASSERT_EQUAL(test_reg_field[3], dev.channel_mask_reg);                          
//     TEST_ASSERT_EQUAL(test_reg_field[4], dev.high_limit_status_reg);                              
//     TEST_ASSERT_EQUAL(test_reg_field[5], dev.low_limit_status_reg);                              
//     TEST_ASSERT_EQUAL(test_reg_field[6], dev.source_voltage_sampling_config_reg);       
//     TEST_ASSERT_EQUAL(test_reg_field[7], dev.ch1_current_sense_sampling_config_reg);      
//     TEST_ASSERT_EQUAL(test_reg_field[8], dev.ch2_current_sense_sampling_config_reg);  

//     uint16_t dummy_curr_lim1 = (test_reg_field[21] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[23];
//     TEST_ASSERT_EQUAL(dummy_curr_lim1, dev.sensor_config_ch1.current_sense_limit_reg);
//     uint16_t dummy_curr_lim2 = (test_reg_field[22] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[24];       
//     TEST_ASSERT_EQUAL(dummy_curr_lim2, dev.sensor_config_ch2.current_sense_limit_reg);    
//     uint16_t dummy_src_vlt1 = (test_reg_field[25] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[27];
//     TEST_ASSERT_EQUAL(dummy_src_vlt1, dev.sensor_config_ch1.source_voltage_limit_reg); 
//     uint16_t dummy_src_vlt2 = (test_reg_field[26] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[28];
//     TEST_ASSERT_EQUAL(dummy_src_vlt2, dev.sensor_config_ch2.source_voltage_limit_reg);

//     TEST_ASSERT_EQUAL(test_reg_field[29], dev.sensor_product_id);                                 
//     TEST_ASSERT_EQUAL(test_reg_field[30], dev.sensor_manufact_id);                             
//     TEST_ASSERT_EQUAL(test_reg_field[31], dev.sensor_revision);  

//     uint16_t dummy_src_vlt_fail = (test_reg_field[27] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[27];
//     TEST_ASSERT_NOT_EQUAL(dummy_src_vlt_fail, dev.sensor_config_ch1.source_voltage_limit_reg); 
//     TEST_ASSERT_NOT_EQUAL(test_reg_field[6], dev.ch2_current_sense_sampling_config_reg);  
// }           

// void test_assign_reading_register_values(void){
//     // Declare test- device struct
//     static struct PAC1720_device dev;
//     uint8_t test_reg_field[32];
//     // Fill test array
//     for(int i = 0; i < 32; i++){
//         test_reg_field[i] = i;
//     }
//     // Verify assignment function
//     assign_reading_register_values_func(&dev, &test_reg_field[READING_REGISTERS_OFFSET]);

//     uint16_t dummy_curr_vlt1 = (test_reg_field[9] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[10];
//     TEST_ASSERT_EQUAL(dummy_curr_vlt1, dev.ch1_readings.v_sense_voltage_reg);     
//     uint16_t dummy_curr_vlt2 = (test_reg_field[11] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[12];
//     TEST_ASSERT_EQUAL(dummy_curr_vlt2, dev.ch2_readings.v_sense_voltage_reg);   
//     uint16_t dummy_src_vlt1 = (test_reg_field[13] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[14];              
//     TEST_ASSERT_EQUAL(dummy_src_vlt1, dev.ch1_readings.v_source_voltage_reg);  
//     uint16_t dummy_src_vlt2 = (test_reg_field[15] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[16];               
//     TEST_ASSERT_EQUAL(dummy_src_vlt2, dev.ch2_readings.v_source_voltage_reg); 
//     uint16_t dummy_pwr1 = (test_reg_field[17] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[18];                 
//     TEST_ASSERT_EQUAL(dummy_pwr1, dev.ch1_readings.power_ratio_reg);  
//     uint16_t dummy_pwr2 = (test_reg_field[19] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[20];                  
//     TEST_ASSERT_EQUAL(dummy_pwr2, dev.ch2_readings.power_ratio_reg);  

//     uint16_t dummy_pwr_fail = (test_reg_field[20] << SHIFT_IN_BYTES_OFFSET) | test_reg_field[21];                  
//     TEST_ASSERT_NOT_EQUAL(dummy_pwr_fail, dev.ch2_readings.power_ratio_reg);
// }   


void test_calculate_BUS_CURRENT (void){
    static struct PAC1720_CH_config dummy_config;
    static struct PAC1720_CH_measurements dummy_meas;
    static struct PAC1720_ch_internal dummy_ch_internal;
    static struct PAC1720_meas_internal dummy_meas_internal;
    dummy_config.ch_internal = &dummy_ch_internal;
    dummy_meas.meas_internal = &dummy_meas_internal;
    // Setup input values
    dummy_meas_internal.v_sense_voltage_reg = 0b0110100110000000;
    dummy_config.CH_current_sense_sampling_time_reg = 0x05;
    // Test FSC not set
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_BUS_CURRENT_func(&dummy_config, &dummy_meas));
    dummy_ch_internal.current_sense_FSC = 2.0f;
    // Test correct current- calculation- denominator selection
    TEST_ASSERT_EQUAL_FLOAT(2047.0f, DENOMINATOR_values_current_sense[dummy_config.CH_current_sense_sampling_time_reg]);
    // Test correct current calculation
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_BUS_CURRENT_func(&dummy_config, &dummy_meas));
    TEST_ASSERT_EQUAL_FLOAT(1.64924276f, dummy_meas.CURRENT);
}

void test_calculate_BUS_VOLTAGE(void){
    static struct PAC1720_CH_config dummy_config;
    static struct PAC1720_CH_measurements dummy_meas;
    static struct PAC1720_ch_internal dummy_ch_internal;
    static struct PAC1720_meas_internal dummy_meas_internal;
    dummy_config.ch_internal = &dummy_ch_internal;
    dummy_meas.meas_internal = &dummy_meas_internal;
    // Setup input values
    dummy_meas_internal.v_source_voltage_reg = 0b1001100110000000;
    dummy_config.CH_source_voltage_sampling_time_reg = 0x02;
    dummy_ch_internal.source_voltage_FSV = 39.96f;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_BUS_VOLTAGE_func(&dummy_config, &dummy_meas));
    TEST_ASSERT_EQUAL_FLOAT(23.9838123f, dummy_meas.SOURCE_VOLTAGE);
}

void test_calculate_BUS_POWER(void){
    static struct PAC1720_CH_config dummy_config;
    static struct PAC1720_CH_measurements dummy_meas;
    static struct PAC1720_ch_internal dummy_ch_internal;
    static struct PAC1720_meas_internal dummy_meas_internal;
    dummy_config.ch_internal = &dummy_ch_internal;
    dummy_meas.meas_internal = &dummy_meas_internal;
    // Test FSP = 0
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_BUS_POWER_func(&dummy_config, &dummy_meas));
    // Setup input values
    dummy_ch_internal.power_sense_FSP = 79.92f;
    dummy_meas_internal.power_ratio_reg = 0b0011100001000111;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_BUS_POWER_func(&dummy_config, &dummy_meas));
    TEST_ASSERT_EQUAL_FLOAT(17.5693493f, dummy_meas.POWER);
}

void test_calculate_SENSED_VOLTAGE (void){
    static struct PAC1720_CH_config dummy_config;
    static struct PAC1720_meas_internal dummy_meas_internal;
    // Set sampling time to allow determination of resolution
    dummy_config.CH_current_sense_sampling_time_reg = 0x05;
    // Test negative voltage return value
    dummy_meas_internal.v_sense_voltage_reg = 0b1001011010000000;
    TEST_ASSERT_EQUAL_FLOAT(-1688.0f, calculate_SENSED_VOLTAGE_func(&dummy_meas_internal.v_sense_voltage_reg, &dummy_config.CH_current_sense_sampling_time_reg));
    dummy_meas_internal.v_sense_voltage_reg = 0xEBC0;
    TEST_ASSERT_EQUAL_FLOAT(-324.0f, calculate_SENSED_VOLTAGE_func(&dummy_meas_internal.v_sense_voltage_reg, &dummy_config.CH_current_sense_sampling_time_reg));
    // Test positive voltage return value
    dummy_meas_internal.v_sense_voltage_reg = 0b0110100110000000;
    TEST_ASSERT_EQUAL_FLOAT(1688.0f, calculate_SENSED_VOLTAGE_func(&dummy_meas_internal.v_sense_voltage_reg, &dummy_config.CH_current_sense_sampling_time_reg));
}

void test_calculate_SOURCE_VOLTAGE(void){
    static struct PAC1720_CH_config dummy_config;
    static struct PAC1720_meas_internal dummy_meas_internal;
    // Test source voltage return value with sample time 2.5 ms (sample reg = 0x00)
    dummy_meas_internal.v_source_voltage_reg = 0b1111111100000000;
    TEST_ASSERT_EQUAL_FLOAT(255.0f, calculate_SOURCE_VOLTAGE_func(&dummy_meas_internal.v_source_voltage_reg, &dummy_config.CH_source_voltage_sampling_time_reg));
     // Set sampling time to allow shifting in correct resolution (11bit here)
    dummy_config.CH_source_voltage_sampling_time_reg = 0x03;
    // Test source voltage return value
    dummy_meas_internal.v_source_voltage_reg = 0b0100010000100000;
    TEST_ASSERT_EQUAL_FLOAT(545.0f, calculate_SOURCE_VOLTAGE_func(&dummy_meas_internal.v_source_voltage_reg, &dummy_config.CH_source_voltage_sampling_time_reg));
    // Set sampling time to allow shifting in correct resolution (10bit here)
    dummy_config.CH_source_voltage_sampling_time_reg = 0x02;
    // Test source voltage return value
    dummy_meas_internal.v_source_voltage_reg = 0b1001100110000000;
    TEST_ASSERT_EQUAL_FLOAT(614.0f, calculate_SOURCE_VOLTAGE_func(&dummy_meas_internal.v_source_voltage_reg, &dummy_config.CH_source_voltage_sampling_time_reg));
}

void test_calculate_FSC (void){
    static struct PAC1720_CH_config dummy_config;
    static struct PAC1720_ch_internal dummy_internal;
    // Test nullpointer fail
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSC_func(NULL));
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSC_func(&dummy_config));
    dummy_config.ch_internal = &dummy_internal;
    // Test resistance = 0
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSC_func(&dummy_config));
    // Test correct FSR selection, reg=0 => select first value
    TEST_ASSERT_EQUAL_FLOAT( 0.01f, FSR_values[dummy_config.CH_current_sense_FSR_reg] );
    // Test correct FSC calculation
    dummy_config.CH_current_sense_FSR_reg = 0x01;
    dummy_config.CH_current_sense_resistor_value = 0.01f;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_FSC_func(&dummy_config));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, dummy_internal.current_sense_FSC);
}

void test_calculate_FSV(void){
    static struct PAC1720_CH_config dummy_config;
    static struct PAC1720_ch_internal dummy_internal;
    // Test nullpointer fail
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSV_func(NULL));
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSV_func(&dummy_config));
    dummy_config.ch_internal = &dummy_internal;
    // Set sampling time for DENOMINATOR value determ.
    dummy_config.CH_source_voltage_sampling_time_reg = 0x02;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_FSV_func(&dummy_config));
    TEST_ASSERT_EQUAL_FLOAT(39.9609375, dummy_internal.source_voltage_FSV);
}

void test_calculate_FSP(void){
    static struct PAC1720_ch_internal dummy_internal;
    // Test FSC is zero
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSP_func(&dummy_internal));
    // Set FSC
    dummy_internal.current_sense_FSC = 2.0f;
    // Test FSV is zero
    TEST_ASSERT_EQUAL(PAC1720_FAILURE, calculate_FSP_func(&dummy_internal));
    // Set FSV and validate FSP
    dummy_internal.source_voltage_FSV = 39.96f;
    TEST_ASSERT_EQUAL(PAC1720_OK, calculate_FSP_func(&dummy_internal));
    TEST_ASSERT_EQUAL_FLOAT(79.92f, dummy_internal.power_sense_FSP);
}

void test_combine_bytes(void){
    uint8_t msb = 0xF0;
    uint8_t lsb = 0x0F;
    uint16_t res = combine_bytes_func(&lsb, &msb);
    TEST_ASSERT_EQUAL_HEX16(0xF00F, res);
}     

void test_twos_complement (void){
    uint16_t int_to_test = 0x0F0A;
    TEST_ASSERT_EQUAL_UINT16(0xF0F6, twos_complement_func(&int_to_test));
}

void test_is_negative_value (void){
    uint16_t int_to_test = 0x7FFF;
    TEST_ASSERT_FALSE(is_negative_value_func(&int_to_test));
    int_to_test = 0x8089;
    TEST_ASSERT_TRUE(is_negative_value_func(&int_to_test));
}

void test_right_bit_shift(void) {
    uint16_t int_to_shift = 0x8000;
    TEST_ASSERT_EQUAL_UINT16(0x01, right_bit_shift_func(&int_to_shift, SHIFT_TO_SIGN_BIT));
}


void test_peripherals_null_pointer_check(void){
    PAC1720_fptr dummy_write = (PAC1720_fptr) &dummy_func;
    PAC1720_fptr dummy_read  = (PAC1720_fptr) &dummy_func;
    delay_fptr dummy_delay   = (delay_fptr)   &dummy_func;
    TEST_ASSERT_EQUAL(PAC1720_NULLPTR_ERROR, peripherals_null_pointer_check_func(NULL, NULL, NULL));
    TEST_ASSERT_EQUAL(PAC1720_NULLPTR_ERROR, peripherals_null_pointer_check_func(dummy_write, NULL, NULL));
    TEST_ASSERT_EQUAL(PAC1720_NULLPTR_ERROR, peripherals_null_pointer_check_func(dummy_write, dummy_read, NULL));
    TEST_ASSERT_EQUAL(PAC1720_OK, peripherals_null_pointer_check_func(dummy_write, dummy_read, dummy_delay));
}

void test_device_null_pointer_check(void) {
    static struct PAC1720_device dev;
    TEST_ASSERT_EQUAL(PAC1720_NULLPTR_ERROR, device_null_pointer_check_func((void*)0));
    TEST_ASSERT_EQUAL(PAC1720_OK, device_null_pointer_check_func(&dev));
}

    // char msg[500];
    // sprintf(msg, "Test: %p %p %p %p", &dev, dev.write, dev.read, dev.delay_ms);
    // TEST_FAIL_MESSAGE(msg);