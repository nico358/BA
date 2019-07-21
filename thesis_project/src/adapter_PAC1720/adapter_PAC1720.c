/**
 * File		
 *
 */

/*! @file 
 *  @brief
 */

/** Header includes **/
#include <stdio.h>
#include "adapter_PAC1720.h"

/** The platform dependend bus interface instance used inside this file */
struct FIELD_BUS_INTERFACE *internal_fieldbus_interface;

/** The platform dependend delay function used in this file */
delay_function_ptr internal_delay;

/* Settings required to setup device with currently applied config ('adapter_init_PAC1720_from_field')*/
// struct PAC1720_device dev_FPGA_VCC = 
// {
// 	   .DEV_sensor_address                                     = 0x4F,
//     .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
//     .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
// };

/* Setup device with default values */
// struct PAC1720_device dev_FPGA_VCC = 
// {
//     .DEV_sensor_address                                    = 0x4F,
//     .DEV_conversion_rate_reg                               = CONVERSION_DEFAULT,
//     .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
//     .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_DEFAULT,
//     .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_DEFAULT,
//     .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_DEFAULT,

//     .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
//     .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_DEFAULT,
//     .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_DEFAULT,
//     .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_DEFAULT,
// };

/* Setup device with all possible settings */
struct PAC1720_device dev_USB_MON = 
{
	.DEV_name_opt                                           = "USB_MONITOR_SENSOR",
	.DEV_sensor_address                                     = 0x4D,
    .DEV_configuration_reg                                  = CONFIG_ALL_CH_ENABLED,
	.DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
	.DEV_one_shot_reg                                       = ONE_SHOT_DEFAULT,
    .DEV_mask_reg                                           = MASK_ALL_CH_ALERT_ASSERT,

    .DEV_CH1_conf.CH_name_opt                               = "USB_VCC",
    .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.15f,
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,

    .DEV_CH2_conf.CH_name_opt                               = "MON_VCC",
    .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
    .DEV_CH2_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
    .DEV_CH2_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
	.DEV_CH2_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    .DEV_CH2_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH2_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
	.DEV_CH2_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
};

struct PAC1720_device dev_FPGA_VCC = {
	.DEV_name_opt                                           = "FPGA_VCC_SENSOR",
	.DEV_sensor_address                                     = 0x4F,
    .DEV_configuration_reg                                  = CONFIG_ALL_CH_ENABLED,
	.DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
	.DEV_one_shot_reg                                       = ONE_SHOT_DEFAULT,
    .DEV_mask_reg                                           = MASK_ALL_CH_ALERT_ASSERT,

    .DEV_CH1_conf.CH_name_opt                               = "FPGA_VCCINT_MON",
    .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,

    .DEV_CH2_conf.CH_name_opt                               = "FPGA_VCCAUX_MON",
    .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
};

struct PAC1720_device dev_WIREL_MCU = {
	.DEV_name_opt                                           = "WIRELESS_MCU_SENSOR",
	.DEV_sensor_address                                     = 0x29,
    .DEV_configuration_reg                                  = CONFIG_ALL_CH_ENABLED,
	.DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
	.DEV_one_shot_reg                                       = ONE_SHOT_DEFAULT,
    .DEV_mask_reg                                           = MASK_ALL_CH_ALERT_ASSERT,

    .DEV_CH1_conf.CH_name_opt                               = "WIRELESS_VCC",
    .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,

    .DEV_CH2_conf.CH_name_opt                               = "MCU_VCC",
    .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
};


/** Function prototypes **/

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
int8_t adapter_fbus_write(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
int8_t adapter_fbus_read(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
void adapter_delay(uint32_t period);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
int8_t fbus_write_loop(uint8_t *data_ptr, const uint16_t len);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
int8_t fbus_read_loop(uint8_t *data_ptr, const uint16_t len);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
bool check_mandatory_dev_settings(struct PAC1720_device *dev_ptr);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
uint8_t poll_fbus(uint8_t *addresses, struct FIELD_BUS_INTERFACE *fieldbus_interface, uint8_t loop_var);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
bool check_peripherals_initialized(void);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
bool sensor_address_out_of_range(const uint8_t address);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
void set_fieldbus_ptr(struct FIELD_BUS_INTERFACE *external_fieldbus_interface);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
void set_delay_ptr(delay_function_ptr external_delay);


/** Function definitions */

void adapter_init_peripherals(struct FIELD_BUS_INTERFACE *fieldbus_interface, delay_function_ptr delay_fptr)
{
    if (fieldbus_interface != NULL && delay_fptr != NULL)
    {
        set_fieldbus_ptr(fieldbus_interface);
        set_delay_ptr(delay_fptr);
    } 
}


int8_t adapter_init_PAC1720_from_field(struct PAC1720_device *dev_ptr)
{
    if (dev_ptr != NULL && check_mandatory_dev_settings(dev_ptr) && check_peripherals_initialized())
    {
        return init_device_PAC1720_from_field(dev_ptr, &adapter_fbus_write, &adapter_fbus_read, &adapter_delay);
    }
    else
    {
        return PAC1720_INIT_ERROR;
    }
}

int8_t adapter_init_PAC1720_user_defined(struct PAC1720_device *dev_ptr)
{
    if (dev_ptr != NULL && check_mandatory_dev_settings(dev_ptr) && check_peripherals_initialized())
    {
        return init_device_PAC1720_user_defined(dev_ptr, &adapter_fbus_write, &adapter_fbus_read, &adapter_delay);
    }
    else
    {
        return PAC1720_INIT_ERROR;
    }
}

void adapter_destroy_PAC1720(struct PAC1720_device *device_ptr)
{
    destroy_device_PAC1720(device_ptr);
}

int8_t adapter_get_measurements_PAC1720(struct PAC1720_device *device_ptr)
{
    return get_all_measurements_PAC1720(device_ptr);
}

int8_t adapter_get_raw_measurements_PAC1720(struct PAC1720_device *device_ptr)
{
    return get_raw_measurements_PAC1720(device_ptr);
}

int8_t adapter_write_one_shot_PAC1720(struct PAC1720_device *device_ptr)
{
    return write_out_one_shot_register(device_ptr);
}

uint8_t adapter_find_sensors(uint8_t *addresses, struct FIELD_BUS_INTERFACE *fieldbus_interface, delay_function_ptr delay_fptr)
{
    uint8_t no_match = 1;
    uint8_t count = 0;
    uint8_t res = 0;

    for (uint8_t loop_var = 0; loop_var < SENSOR_ADDRESS_NUMBER; loop_var++)
    {
        while (no_match && count <= max_search_attempts)
        {
            no_match = poll_fbus(addresses, fieldbus_interface, loop_var);

            if (no_match)
            {
                count++;
                delay_fptr(10);
            } 
        }

        if(!no_match)
        {
            res++;
        }
        no_match = 1;
        count = 0;
    }
    return res;
}

/** User defined i2c write function */
int8_t adapter_fbus_write(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len)
{   /** (Blocking) Connect to sensor, return error if fails */
    uint8_t result = PAC1720_OK;

    internal_fieldbus_interface->startWait((sensor_address << BUS_ADDRESS_SHIFT) + I2C_WRITE); 
    result = internal_fieldbus_interface->write(reg_address);
    if(result != PAC1720_OK) 
    {
        return result;
    }

    result = fbus_write_loop(data_ptr, len);

    /** Stop communication */
    internal_fieldbus_interface->stop();
    return result;
}

/** User defined i2c read function */
int8_t adapter_fbus_read(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len)
{   /** (Blocking) Connect to sensor, return error if fails */
    uint8_t result = PAC1720_OK;

    internal_fieldbus_interface->startWait((sensor_address << BUS_ADDRESS_SHIFT) + I2C_WRITE);
    result = internal_fieldbus_interface->write(reg_address); 
    if(result != PAC1720_OK)
    {
        return result;
    }
    /* (Blocking) Repeat start in read mode, return error if fails  */
    result = internal_fieldbus_interface->repStart((sensor_address << BUS_ADDRESS_SHIFT) + I2C_READ);
    if(result != PAC1720_OK) 
    {
        return result;
    }
    
    result = fbus_read_loop(data_ptr, len);

    /** Stop communication */
    internal_fieldbus_interface->stop();
    return result;
}

/* User defined delay function */
void adapter_delay(uint32_t period)
{
    /* Provided delay function */
    internal_delay(period);
}

int8_t fbus_write_loop(uint8_t *data_ptr, const uint16_t len)
{
    uint8_t result = PAC1720_OK;
    /** Write to #len registers, increase the address #len times, return error if fails */
    for(uint16_t i = 0; i < len; i++)
    {
        result = internal_fieldbus_interface->write(*data_ptr);
        if(result != PAC1720_OK) return result;
        data_ptr++;
    }
    return result;
}

int8_t fbus_read_loop(uint8_t *data_ptr, const uint16_t len)
{
    uint8_t result = PAC1720_OK;
    /* Read from #len registers, increase the address #len times */
    for(uint16_t i = 0; i < len; i++)
    {   /** Read register and send ACK */
        if(i < len -1)  *data_ptr = internal_fieldbus_interface->readAck();
        /* After the last read send NACK */
        else            *data_ptr = internal_fieldbus_interface->readNak(); 
        data_ptr++;
    }
    return result;
}

uint8_t poll_fbus(uint8_t *addresses, struct FIELD_BUS_INTERFACE *fieldbus_interface, uint8_t loop_var)
{
    uint8_t sensor_addr = PAC1720_addresses[loop_var];

    uint8_t no_match = fieldbus_interface->start((sensor_addr << BUS_ADDRESS_SHIFT) + I2C_WRITE);
    fieldbus_interface->stop();

    if(!no_match)
    {
        uint8_t *offset = addresses + loop_var;
        *offset = sensor_addr;
    }
    return no_match;
}

bool check_peripherals_initialized(void)
{
    return (internal_fieldbus_interface != NULL && internal_delay != NULL);
}

bool check_mandatory_dev_settings(struct PAC1720_device *dev_ptr) 
{
    if ( sensor_address_out_of_range(dev_ptr->DEV_sensor_address)               
         || dev_ptr->DEV_CH1_conf.CH_current_sense_resistor_value == 0  
         || dev_ptr->DEV_CH2_conf.CH_current_sense_resistor_value == 0 )
    {
        return false;
    }
    return true;
}
      
bool sensor_address_out_of_range(const uint8_t address)
{
    if(address == 0x18 || (address > 0x27 && address < 0x2F) || (address > 0x47 && address < 0x50))
    {
        return false;
    }
    return true;
}

void set_fieldbus_ptr(struct FIELD_BUS_INTERFACE *external_fieldbus_interface)
{
    internal_fieldbus_interface = external_fieldbus_interface;
}

void set_delay_ptr(delay_function_ptr external_delay)
{
    internal_delay = external_delay;
}

const void* get_ADAPTER_TEST_FPTR_FIELD(void)
{
    static const void* test_fptr_field[] =  {
                                                 (void*) &adapter_fbus_write,
                                                 (void*) &adapter_fbus_read,
                                                 (void*) &adapter_delay,
                                                 (void*) &sensor_address_out_of_range,
                                                 (void*) NULL,
                                                 (void*) &poll_fbus,
                                                 (void*) &set_fieldbus_ptr,
                                                 (void*) &set_delay_ptr,
                                                 (void*) &check_mandatory_dev_settings,
                                                 (void*) &check_peripherals_initialized,
                                                 (void*) &fbus_write_loop,
                                                 (void*) &fbus_read_loop
                                            };

    return &test_fptr_field;
}

void print_measurements_PAC1720(struct PAC1720_device * dev, debugWriteLine_fptr debug_fptr, uint16_t counter)
{
    char msg[256];

    sprintf(msg, "%u ", dev->DEV_CH1_measurements.meas_cnt);
    debug_fptr(msg);
    sprintf(msg, "%s %f %f %f ", dev->DEV_CH1_conf.CH_name_opt, dev->DEV_CH1_measurements.CURRENT, dev->DEV_CH1_measurements.SOURCE_VOLTAGE, dev->DEV_CH1_measurements.POWER);
    debug_fptr(msg);
    sprintf(msg, "%s %f %f %f\r\n", dev->DEV_CH2_conf.CH_name_opt, dev->DEV_CH2_measurements.CURRENT, dev->DEV_CH2_measurements.SOURCE_VOLTAGE, dev->DEV_CH2_measurements.POWER);
    debug_fptr(msg);
}

void print_raw_measurements_PAC1720(struct PAC1720_device * dev, debugWriteLine_fptr debug_fptr)
{
    char msg[256];

    debug_fptr("{\r\n");
    sprintf(msg, "[Name: %s, COUNT: %d]\r\n", dev->DEV_name_opt, dev->DEV_CH1_measurements.meas_cnt);
    debug_fptr(msg);
    sprintf(msg, "Name: %s, v_sense_voltage_reg: %x,  v_source_voltage_reg: %x, power_ratio_reg: %x\r\n", dev->DEV_CH1_conf.CH_name_opt, get_channel_sense_voltage_read(&dev->DEV_CH1_measurements), get_channel_src_voltage_read(&dev->DEV_CH1_measurements), get_channel_pwr_ratio_read(&dev->DEV_CH1_measurements));
    debug_fptr(msg);
    sprintf(msg, "Name: %s, v_sense_voltage_reg: %x,  v_source_voltage_reg: %x, power_ratio_reg: %x\r\n", dev->DEV_CH2_conf.CH_name_opt, get_channel_sense_voltage_read(&dev->DEV_CH2_measurements), get_channel_src_voltage_read(&dev->DEV_CH2_measurements), get_channel_pwr_ratio_read(&dev->DEV_CH2_measurements));
    debug_fptr(msg);
    debug_fptr("}\r\n\r\n\r\n");
}
 
void debug_PAC1720(struct PAC1720_device * dev, debugWriteLine_fptr debug_fptr){
    char msg[512];

    sprintf(msg, "Name: %s,\r\n\r\naddr: %x, conf_reg: %x, conv_rate_reg: %x, oneshot_reg: %x, mask_reg: %x\r\n\r\n", dev->DEV_name_opt, dev->DEV_sensor_address, dev->DEV_configuration_reg, dev->DEV_conversion_rate_reg, dev->DEV_one_shot_reg, dev->DEV_mask_reg);
    debug_fptr(msg);

    uint8_t high_lim_status_reg = 0;
    high_lim_status_reg |= dev->DEV_CH1_measurements.conversion_done << 7;
    high_lim_status_reg |= dev->DEV_CH2_measurements.sense_voltage_high_limit << 3;
    high_lim_status_reg |= dev->DEV_CH2_measurements.source_voltage_high_limit << 2;
    high_lim_status_reg |= dev->DEV_CH1_measurements.sense_voltage_high_limit << 1;
    high_lim_status_reg |= dev->DEV_CH1_measurements.source_voltage_high_limit;
    uint8_t low_lim_status_reg = 0;
    low_lim_status_reg |= dev->DEV_CH2_measurements.sense_voltage_low_limit << 3;
    low_lim_status_reg |= dev->DEV_CH2_measurements.source_voltage_low_limit << 2;
    low_lim_status_reg |= dev->DEV_CH1_measurements.sense_voltage_low_limit << 1;
    low_lim_status_reg |= dev->DEV_CH1_measurements.source_voltage_low_limit;
    sprintf(msg, "high_lim_status_reg: %x, low_lim_status_reg: %x\r\n\r\n", high_lim_status_reg, low_lim_status_reg);
    debug_fptr(msg);

    uint8_t Vsrc_sample_reg = 0;
    Vsrc_sample_reg |= dev->DEV_CH2_conf.CH_source_voltage_sampling_time_reg << 6;
    Vsrc_sample_reg |= dev->DEV_CH2_conf.CH_source_voltage_sampling_average_reg << 4;
    Vsrc_sample_reg |= dev->DEV_CH1_conf.CH_source_voltage_sampling_time_reg << 2;
    Vsrc_sample_reg |= dev->DEV_CH1_conf.CH_source_voltage_sampling_average_reg;
    uint8_t Vsense_ch1_sample_reg = 0;
    Vsense_ch1_sample_reg |= dev->DEV_CH1_conf.CH_current_sense_sampling_time_reg << 4;
    Vsense_ch1_sample_reg |= dev->DEV_CH1_conf.CH_current_sense_sampling_average_reg << 2;
    Vsense_ch1_sample_reg |= dev->DEV_CH1_conf.CH_current_sense_FSR_reg;
    uint8_t Vsense_ch2_sample_reg = 0;
    Vsense_ch2_sample_reg |= dev->DEV_CH2_conf.CH_current_sense_sampling_time_reg << 4;
    Vsense_ch2_sample_reg |= dev->DEV_CH2_conf.CH_current_sense_sampling_average_reg << 2;
    Vsense_ch2_sample_reg |= dev->DEV_CH2_conf.CH_current_sense_FSR_reg;
    sprintf(msg, "Vsrc_sample_reg: %x, Vsense_ch1_sample_reg: %x, Vsense_ch2_sample_reg: %x\r\n\r\n", Vsrc_sample_reg, Vsense_ch1_sample_reg, Vsense_ch2_sample_reg);
    debug_fptr(msg);

    sprintf(msg, "Name: %s,\r\nRes: %f\r\n", dev->DEV_CH1_conf.CH_name_opt, dev->DEV_CH1_conf.CH_current_sense_resistor_value);
    debug_fptr(msg);
    sprintf(msg, "FSC: %f, FSV: %f, FSP: %f\r\n", get_channel_FSC(&dev->DEV_CH1_conf), get_channel_FSV(&dev->DEV_CH1_conf), get_channel_FSP(&dev->DEV_CH1_conf));
    debug_fptr(msg);

    sprintf(msg, "CH1 COUNT: %d,\r\n", dev->DEV_CH1_measurements.meas_cnt);
    debug_fptr(msg);
    sprintf(msg, "v_sense_voltage_reg: %x,  v_source_voltage_reg: %x, power_ratio_reg: %x\r\n", get_channel_sense_voltage_read(&dev->DEV_CH1_measurements), get_channel_src_voltage_read(&dev->DEV_CH1_measurements), get_channel_pwr_ratio_read(&dev->DEV_CH1_measurements));
    debug_fptr(msg);
    sprintf(msg, "CH1 SENSE_VOLTAGE: %fmV, CURRENT: %fA, SOURCE_VOLTAGE: %fV, POWER: %fW\r\n\r\n", dev->DEV_CH1_measurements.SENSE_VOLTAGE, dev->DEV_CH1_measurements.CURRENT, dev->DEV_CH1_measurements.SOURCE_VOLTAGE, dev->DEV_CH1_measurements.POWER);
    debug_fptr(msg);

    sprintf(msg, "Name: %s,\r\nRes: %f\r\n", dev->DEV_CH2_conf.CH_name_opt, dev->DEV_CH2_conf.CH_current_sense_resistor_value);
    debug_fptr(msg);
    sprintf(msg, "FSC: %f, FSV: %f, FSP: %f\r\n\r\n", get_channel_FSC(&dev->DEV_CH2_conf), get_channel_FSV(&dev->DEV_CH2_conf), get_channel_FSP(&dev->DEV_CH2_conf));
    debug_fptr(msg);

    sprintf(msg, "CH2 COUNT: %d,\r\n", dev->DEV_CH2_measurements.meas_cnt);
    debug_fptr(msg);
    sprintf(msg, "v_sense_voltage_reg: %x,  v_source_voltage_reg: %x, power_ratio_reg: %x\r\n", get_channel_sense_voltage_read(&dev->DEV_CH2_measurements), get_channel_src_voltage_read(&dev->DEV_CH2_measurements), get_channel_pwr_ratio_read(&dev->DEV_CH2_measurements));
    debug_fptr(msg);
    sprintf(msg, "CH2 SENSE_VOLTAGE: %fmV, CURRENT: %fA, SOURCE_VOLTAGE: %fV, POWER: %fW\r\n\r\n", dev->DEV_CH2_measurements.SENSE_VOLTAGE, dev->DEV_CH2_measurements.CURRENT, dev->DEV_CH2_measurements.SOURCE_VOLTAGE, dev->DEV_CH2_measurements.POWER);
    debug_fptr(msg);

    sprintf(msg, "CH1_current_sense_high_limit_reg: %x, CH2_current_sense_high_limit_reg: %x\r\n", dev->DEV_CH1_conf.CH_current_sense_high_limit_reg, dev->DEV_CH2_conf.CH_current_sense_high_limit_reg);
    debug_fptr(msg);
    sprintf(msg, "CH1_current_sense_low_limit_reg: %x, CH2_current_sense_low_limit_reg: %x\r\n", dev->DEV_CH1_conf.CH_current_sense_low_limit_reg, dev->DEV_CH2_conf.CH_current_sense_low_limit_reg);
    debug_fptr(msg);
    sprintf(msg, "CH1_source_voltage_high_limit_reg: %x, CH2_source_voltage_high_limit_reg: %x\r\n", dev->DEV_CH1_conf.CH_source_voltage_high_limit_reg, dev->DEV_CH2_conf.CH_source_voltage_high_limit_reg);
    debug_fptr(msg);
    sprintf(msg, "CH1_source_voltage_low_limit_reg: %x, CH2_source_voltage_low_limit_reg: %x\r\n\r\n", dev->DEV_CH1_conf.CH_source_voltage_low_limit_reg, dev->DEV_CH2_conf.CH_source_voltage_low_limit_reg);
    debug_fptr(msg);

    sprintf(msg, "id: %x, man: %x, rev: %x\r\n\r\n\r\n\r\n", get_sensor_product_id(dev), get_sensor_manufact_id(dev), get_sensor_revision_id(dev));
    debug_fptr(msg);
}