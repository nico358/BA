#include "unity.h"
#include "src/adapter_PAC1720/adapter_PAC1720.h"

/* Declare internal structs to allow access in this file */
struct 	PAC1720_internal
{
    /* Bus read function pointer */
	PAC1720_fptr read;
	/* Bus write function pointer */
	PAC1720_fptr write;
	/* Delay function pointer */
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
    /* Full Scale Current (FSC) */
	float 		current_sense_FSC;
    /* Full Scale Voltage (FSV) */
	float 		source_voltage_FSV;
	/* Full Scale Power (FSP)  */
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

uint8_t readAck_call_global;
uint8_t readNak_call_global;

// Store values written by mock_i2c_write()
uint8_t write_args[25];



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
    // Fill array with args from init function
    if(mock_i2c_write_call < 25){
        write_args[mock_i2c_write_call] = data;
    }
    
    mock_i2c_write_call++;
    mock_i2c_write_arg = data;
	return PAC1720_OK;
}

unsigned char mock_i2c_readAck(void){
    // Return sensor info regs
    if(readAck_call_global < 2){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x0D;
    }
    // Return high limit status reg, conv flag set
    if(readAck_call_global == 2){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x80;
    }
    // Return high byte of ch1 sense voltage
    if(readAck_call_global == 3){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x69;
    }
    // Return low byte of ch1 sense voltage
    if(readAck_call_global == 4){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x80;
    }
    // Return high byte of ch2 sense voltage
    if(readAck_call_global == 5){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x96;
    }
    // Return low byte of ch2 sense voltage
    if(readAck_call_global == 6){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x80;
    }
    // Return high byte of ch1 source voltage
    if(readAck_call_global == 7){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x44;
    }
    // Return low byte of ch1 source voltage
    if(readAck_call_global == 8){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x20;
    }
    // Return high byte of ch2 source voltage
    if(readAck_call_global == 9){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x99;
    }
    // Return low byte of ch2 source voltage
    if(readAck_call_global == 10){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x80;
    }
    // Return high byte of ch1 power ratio
    if(readAck_call_global == 11){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x38;
    }
    // Return low byte of ch1 power ratio
    if(readAck_call_global == 12){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x47;
    }
    // Return high byte of ch2 power ratio
    if(readAck_call_global == 13){
        readAck_call_global++;
        mock_i2c_readAck_call++;
        return 0x7E;
    }
    readAck_call_global++;
    mock_i2c_readAck_call++;
    return 0xFF;
}

unsigned char mock_i2c_readNak(void){
    // Return sensor not sleeping in 1st initialization call
    if(readNak_call_global <= MAX_ATTEMPTS_SET_SLEEP_MODE){
        readNak_call_global++;
        return 0x01;
    } 
    // Return sensor sleeps in 2nd initialization call 
    if(readNak_call_global == MAX_ATTEMPTS_SET_SLEEP_MODE +1){
        mock_i2c_readNak_call++;
        readNak_call_global++;
        return CONFIG_STANDBY;
    } 
    // Return 0xA for sensor revision id
    if(readNak_call_global == MAX_ATTEMPTS_SET_SLEEP_MODE +2){
        mock_i2c_readNak_call++;
        readNak_call_global++;
        return 0x0A;
    } 
    // Return 0x03 for low limit status reg
    if(readNak_call_global == MAX_ATTEMPTS_SET_SLEEP_MODE +3){
        mock_i2c_readNak_call++;
        readNak_call_global++;
        return 0x03;
    } 
    // Return low byte of ch2 power ratio
    if(readNak_call_global == MAX_ATTEMPTS_SET_SLEEP_MODE +4){
        mock_i2c_readNak_call++;
        readNak_call_global++;
        return 0xC7;
    } 
    mock_i2c_readNak_call++;
    readNak_call_global++;
    return 0xFF;
}

/* External delay function spy */
void mock_user_delay(uint32_t period){
    mock_delay_arg = period;
    mock_delay_call++;
}

/** Field- Bus communication struct from external */
struct BUS_INTERFACE dummy_i2c = {
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
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_80ms,
    /* Current sense sample averaging of channel one */
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    /* Full scale voltage range for current sensing */
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
    /* High limit of current for channel one */
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
    /* Low limit of current for channel one */
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    /* Sampling time of source voltage sense */
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_20ms,
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
    .DEV_CH2_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGES_2,
    /* Full scale voltage range for current sensing */
    .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
    /* High limit of current for channel two */
    .DEV_CH2_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
    /* Low limit of current for channel two */
	.DEV_CH2_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    /* Sampling time of source voltage sense */
    .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    /* Source voltage sample averaging of channel two */
    .DEV_CH2_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGES_2,
    /* Source voltage high limit for channel two */
    .DEV_CH2_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
    /* Source voltage low limit for channel two */
	.DEV_CH2_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
};

void setUp(void) {
    // Set up bus communication and delay function in adapter
    adapter_init_peripherals(&dummy_i2c, &mock_user_delay);
}

void tearDown(void) {
    // Reset all verification params
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

    for(int i = 0; i < 25; i++){
        write_args[i] = 0;
    }
}

// Test init fail by using sensor sleep mode request (mock_i2c_readNak return 0x1 in 1st run)
void test_driver_initialize_fail(void){
    TEST_ASSERT_EQUAL(PAC1720_INIT_ERROR, adapter_init_PAC1720_user_defined(&test_dev));  
}

// Test init function of adapter & driver
// Values are injected by spy functions
void test_driver_initialize(void){
    TEST_ASSERT_EQUAL(PAC1720_OK, adapter_init_PAC1720_user_defined(&test_dev));  
    // Check spy calls of init 
    TEST_ASSERT_EQUAL(6, mock_i2c_start_wait_call);
    TEST_ASSERT_EQUAL(22, mock_i2c_write_call);
    TEST_ASSERT_EQUAL(6, mock_i2c_stop_call);
    TEST_ASSERT_EQUAL(2, mock_i2c_rep_start_call);
    TEST_ASSERT_EQUAL(2, mock_i2c_readAck_call);
    TEST_ASSERT_EQUAL(2, mock_i2c_readNak_call);
    // Test assignment to empty name
    TEST_ASSERT_EQUAL_STRING("None", test_dev.DEV_CH2_conf.CH_name_opt);
    // Check returned values of spies in internal pointer
    struct 	PAC1720_internal *internal = test_dev.internal;
    TEST_ASSERT_EQUAL(0x0D, internal->sensor_product_id);
    TEST_ASSERT_EQUAL(0x0D, internal->sensor_manufact_id);
    TEST_ASSERT_EQUAL(0x0A, internal->sensor_revision);
    // Check FSx calculations
    struct PAC1720_ch_internal *ch1_internal = test_dev.DEV_CH1_conf.ch_internal;
    TEST_ASSERT_EQUAL_FLOAT(2.0f, ch1_internal->current_sense_FSC);
    TEST_ASSERT_EQUAL_FLOAT(39.98046875f, ch1_internal->source_voltage_FSV);
    TEST_ASSERT_EQUAL_FLOAT(79.9609375f, ch1_internal->power_sense_FSP);
    struct PAC1720_ch_internal *ch2_internal = test_dev.DEV_CH2_conf.ch_internal;
    TEST_ASSERT_EQUAL_FLOAT(2.0f, ch2_internal->current_sense_FSC);
    TEST_ASSERT_EQUAL_FLOAT(39.84375f, ch2_internal->source_voltage_FSV);
    TEST_ASSERT_EQUAL_FLOAT(79.6875f, ch2_internal->power_sense_FSP);
    // Check sensor sleep set
    TEST_ASSERT_EQUAL(configuration_register_address, write_args[0]);
    TEST_ASSERT_EQUAL(CONFIG_STANDBY, write_args[1]);
    // Check read config reg
    TEST_ASSERT_EQUAL(configuration_register_address, write_args[2]);
    // Check config registers set
    TEST_ASSERT_EQUAL(configuration_register_address, write_args[3]);
    TEST_ASSERT_EQUAL(CONFIG_ALL_CH_ENABLED, write_args[4]);
    TEST_ASSERT_EQUAL(CONVERSION_CONTINIOUS, write_args[5]);
    TEST_ASSERT_EQUAL(ONE_SHOT_DEFAULT, write_args[6]);
    TEST_ASSERT_EQUAL(MASK_ALL_CH_ALERT_ASSERT, write_args[7]);
    // Check sample registers set
    TEST_ASSERT_EQUAL(v_source_sampling_configuration_register_address, write_args[8]);
    TEST_ASSERT_EQUAL(0x1C, write_args[9]); // 11011100 = Ch2 vsource sampling: 20ms + avg: 2 + Ch1 vsource sampling: 20ms + avg: 0
    TEST_ASSERT_EQUAL(0x51, write_args[10]);
    TEST_ASSERT_EQUAL(0x05, write_args[11]);
    // Check limit regs set
    TEST_ASSERT_EQUAL(ch1_sense_voltage_high_limit_register_address, write_args[12]);
    TEST_ASSERT_EQUAL(CURRENT_SENSE_HIGH_LIMIT_DEFAULT, write_args[13]);
    TEST_ASSERT_EQUAL(CURRENT_SENSE_HIGH_LIMIT_DEFAULT, write_args[14]);
    TEST_ASSERT_EQUAL(CURRENT_SENSE_LOW_LIMIT_DEFAULT, write_args[15]);
    TEST_ASSERT_EQUAL(CURRENT_SENSE_LOW_LIMIT_DEFAULT, write_args[16]);
    TEST_ASSERT_EQUAL(SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT, write_args[17]);
    TEST_ASSERT_EQUAL(SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT, write_args[18]);
    TEST_ASSERT_EQUAL(SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT, write_args[19]);
    TEST_ASSERT_EQUAL(SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT, write_args[20]);
    // Check read info regs
    TEST_ASSERT_EQUAL(product_id_register_address, write_args[21]);
    // Check nothing else written
    TEST_ASSERT_EQUAL(0, write_args[22]);
    TEST_ASSERT_EQUAL(0, write_args[23]);
}

// Test measurement function of driver
// Values are injected by spy functions
void test_driver_calculate_measurements(void){
    TEST_ASSERT_EQUAL(PAC1720_OK, adapter_get_measurements_PAC1720(&test_dev));
    // Check sensor has finished conversion and limit statuses
    TEST_ASSERT_TRUE(test_dev.DEV_CH1_measurements.conversion_done);
    TEST_ASSERT_FALSE(test_dev.DEV_CH1_measurements.sense_voltage_high_limit);
    TEST_ASSERT_FALSE(test_dev.DEV_CH2_measurements.sense_voltage_high_limit);
    TEST_ASSERT_FALSE(test_dev.DEV_CH1_measurements.source_voltage_high_limit);
    TEST_ASSERT_FALSE(test_dev.DEV_CH2_measurements.source_voltage_high_limit);
    TEST_ASSERT_TRUE(test_dev.DEV_CH1_measurements.sense_voltage_low_limit);
    TEST_ASSERT_TRUE(test_dev.DEV_CH1_measurements.source_voltage_low_limit);
    TEST_ASSERT_FALSE(test_dev.DEV_CH2_measurements.sense_voltage_low_limit);
    TEST_ASSERT_FALSE(test_dev.DEV_CH2_measurements.source_voltage_low_limit);
    // Check read values channel 1
    struct 	PAC1720_meas_internal *meas_internal = test_dev.DEV_CH1_measurements.meas_internal;
    TEST_ASSERT_EQUAL(0x6980, meas_internal->v_sense_voltage_reg);
    TEST_ASSERT_EQUAL(0x4420, meas_internal->v_source_voltage_reg);
    TEST_ASSERT_EQUAL(0x3847, meas_internal->power_ratio_reg);
    // Check calculated values channel 1
    TEST_ASSERT_EQUAL_FLOAT(1.649243f, test_dev.DEV_CH1_measurements.CURRENT);
    TEST_ASSERT_EQUAL_FLOAT(0.01649243f, test_dev.DEV_CH1_measurements.SENSE_VOLTAGE);
    TEST_ASSERT_EQUAL_FLOAT(10.64453125f, test_dev.DEV_CH1_measurements.SOURCE_VOLTAGE);
    TEST_ASSERT_EQUAL_FLOAT(17.57835091f, test_dev.DEV_CH1_measurements.POWER);
    // Check read values channel 2
    meas_internal = test_dev.DEV_CH2_measurements.meas_internal;
    TEST_ASSERT_EQUAL(0x9680, meas_internal->v_sense_voltage_reg);
    TEST_ASSERT_EQUAL(0x9980, meas_internal->v_source_voltage_reg);
    TEST_ASSERT_EQUAL(0x7EC7, meas_internal->power_ratio_reg);
    // Check calculated values channel 2
    TEST_ASSERT_EQUAL_FLOAT(-1.650793651f, test_dev.DEV_CH2_measurements.CURRENT);
    TEST_ASSERT_EQUAL_FLOAT(-0.01650793651, test_dev.DEV_CH2_measurements.SENSE_VOLTAGE);
    TEST_ASSERT_EQUAL_FLOAT(23.90625f, test_dev.DEV_CH2_measurements.SOURCE_VOLTAGE);
    TEST_ASSERT_EQUAL_FLOAT(39.4637642, test_dev.DEV_CH2_measurements.POWER);
}
