/**
 * File		
 *
 */

/*! @file 
 *  @brief
 */

/** Header includes **/
#include "adapter_PAC1720.h"


/** The platform dependend bus interface instance used inside this file */
struct FIELD_BUS_INTERFACE *internal_fieldbus_interface;

/** The platform dependend delay function used in this file */
delay_function_ptr internal_delay;

struct PAC1720_device dev_USB_MON = {
	.DEV_name_opt                                           = "USB_MON",
	.DEV_sensor_address                                     = 0x4D,
	.DEV_channels                                           = BOTH_CHANNELS,
    .DEV_configuration_reg                                  = 0,
	.DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
	.DEV_one_shot_reg                                       = 0,

    .DEV_CH1_conf.CH_name_opt                               = "USB_VCC",
    .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.15f,
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_80ms,
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_80mV,
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = 0,
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = 0,
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_20ms,
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = 0,
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = 0,
    .DEV_CH1_conf.CH_mask_reg                               = 0,

    .DEV_CH2_conf.CH_name_opt                               = "MON_VCC",
    .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_80ms,
    .DEV_CH2_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_80mV,
    .DEV_CH2_conf.CH_current_sense_high_limit_reg           = 0,
	.DEV_CH2_conf.CH_current_sense_low_limit_reg            = 0,
    .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_20ms,
    .DEV_CH2_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH2_conf.CH_source_voltage_high_limit_reg          = 0,
	.DEV_CH2_conf.CH_source_voltage_low_limit_reg           = 0,
    .DEV_CH2_conf.CH_mask_reg                               = 0,
};

struct PAC1720_device dev_FPGA_VCC = {
	.DEV_name_opt                                           = "FPGA_VCC",
	.DEV_sensor_address                                     = 0x4F,
	.DEV_channels                                           = BOTH_CHANNELS,
    .DEV_configuration_reg                                  = 0,
	.DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
	.DEV_one_shot_reg                                       = 0,

    .DEV_CH1_conf.CH_name_opt                               = "FPGA_VCCINT_MON",
    .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_80ms,
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_80mV,
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = 0,
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = 0,
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_20ms,
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = 0,
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = 0,
    .DEV_CH1_conf.CH_mask_reg                               = 0,

    .DEV_CH2_conf.CH_name_opt                               = "FPGA_VCCAUX_MON",
    .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_80ms,
    .DEV_CH2_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_80mV,
    .DEV_CH2_conf.CH_current_sense_high_limit_reg           = 0,
	.DEV_CH2_conf.CH_current_sense_low_limit_reg            = 0,
    .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_20ms,
    .DEV_CH2_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH2_conf.CH_source_voltage_high_limit_reg          = 0,
	.DEV_CH2_conf.CH_source_voltage_low_limit_reg           = 0,
    .DEV_CH2_conf.CH_mask_reg                               = 0,
};

struct PAC1720_device dev_WIREL_MCU = {
	.DEV_name_opt                                           = "WIREL_MCU",
	.DEV_sensor_address                                     = 0x29,
	.DEV_channels                                           = BOTH_CHANNELS,
    .DEV_configuration_reg                                  = 0,
	.DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
	.DEV_one_shot_reg                                       = 0,

    .DEV_CH1_conf.CH_name_opt                               = "WIRELESS_VCC",
    .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_80ms,
    .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_80mV,
    .DEV_CH1_conf.CH_current_sense_high_limit_reg           = 0,
	.DEV_CH1_conf.CH_current_sense_low_limit_reg            = 0,
    .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_20ms,
    .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = 0,
	.DEV_CH1_conf.CH_source_voltage_low_limit_reg           = 0,
    .DEV_CH1_conf.CH_mask_reg                               = 0,

    .DEV_CH2_conf.CH_name_opt                               = "MCU_VCC",
    .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
    .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_80ms,
    .DEV_CH2_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_80mV,
    .DEV_CH2_conf.CH_current_sense_high_limit_reg           = 0,
	.DEV_CH2_conf.CH_current_sense_low_limit_reg            = 0,
    .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_20ms,
    .DEV_CH2_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
    .DEV_CH2_conf.CH_source_voltage_high_limit_reg          = 0,
	.DEV_CH2_conf.CH_source_voltage_low_limit_reg           = 0,
    .DEV_CH2_conf.CH_mask_reg                               = 0,
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
bool channels_out_of_range(const ACTIVE_CHANNELS channels);

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


int8_t adapter_init_PAC1720(struct PAC1720_device *dev_ptr)
{
    if (dev_ptr != NULL && check_mandatory_dev_settings(dev_ptr) && check_peripherals_initialized())
    {
        return init_device_PAC1720(dev_ptr, &adapter_fbus_write, &adapter_fbus_read, &adapter_delay);
    }
    else
    {
        return PAC1720_INIT_ERROR;
    }
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
         || channels_out_of_range(dev_ptr->DEV_channels)               
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

bool channels_out_of_range(const ACTIVE_CHANNELS channels)
{
    if(channels >= FIRST_CHANNEL && channels <= BOTH_CHANNELS)
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
                                                 (void*) &channels_out_of_range,
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


// void print_measurements(void)
// {
//     char msg[256];
//     get_measurements(&dev_USB_MON);
//     get_measurements(&dev_FPGA_VCC);
//     get_measurements(&dev_WIREL_MCU);

//     debugWriteLine("{\r\n");
//     sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_USB_MON.sensor_config_ch1.name, dev_USB_MON.ch1_readings.res_CURRENT, dev_USB_MON.ch1_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch1_readings.res_POWER);
//     debugWriteLine(msg);
//     sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_USB_MON.sensor_config_ch2.name, dev_USB_MON.ch2_readings.res_CURRENT, dev_USB_MON.ch2_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch2_readings.res_POWER);
//     debugWriteLine(msg);

//     sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_FPGA_VCC.sensor_config_ch1.name, dev_FPGA_VCC.ch1_readings.res_CURRENT, dev_FPGA_VCC.ch1_readings.res_SOURCE_VOLTAGE, dev_FPGA_VCC.ch1_readings.res_POWER);
//     debugWriteLine(msg);
//     sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_FPGA_VCC.sensor_config_ch2.name, dev_FPGA_VCC.ch2_readings.res_CURRENT, dev_FPGA_VCC.ch2_readings.res_SOURCE_VOLTAGE, dev_FPGA_VCC.ch2_readings.res_POWER);
//     debugWriteLine(msg);

//     sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_WIREL_MCU.sensor_config_ch1.name, dev_WIREL_MCU.ch1_readings.res_CURRENT, dev_WIREL_MCU.ch1_readings.res_SOURCE_VOLTAGE, dev_WIREL_MCU.ch1_readings.res_POWER);
//     debugWriteLine(msg);
//     sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_WIREL_MCU.sensor_config_ch2.name, dev_WIREL_MCU.ch2_readings.res_CURRENT, dev_WIREL_MCU.ch2_readings.res_SOURCE_VOLTAGE, dev_WIREL_MCU.ch2_readings.res_POWER);
//     debugWriteLine(msg);
//     debugWriteLine("}\r\n\r\n\r\n");
// }

// void print_USB_MON(void){
//         char msg[512];
//         sprintf(msg, "Name: %s, addr: %x, channels: %x\r\n", dev_USB_MON.name,  dev_USB_MON.sensor_address,  dev_USB_MON.channels); 
//         debugWriteLine(msg);
//         sprintf(msg, "conf_reg: %x, conv_rate: %x, oneshot: %x,\r\n",  dev_USB_MON.configuration_reg,  dev_USB_MON.conversion_rate_reg,  dev_USB_MON.one_shot_reg); 
//         debugWriteLine(msg);
//         sprintf(msg, "mask: %x, high_l: %x, low_l: %x, source_sample: %x,\r\n", dev_USB_MON.channel_mask_reg,  dev_USB_MON.high_limit_status_reg,  dev_USB_MON.low_limit_status_reg,  dev_USB_MON.source_voltage_sampling_config_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "sense_sample1: %x, sense_sample2: %x, id: %x, man: %x, rev: %x\r\n\r\n", dev_USB_MON.ch1_current_sense_sampling_config_reg,  dev_USB_MON.ch2_current_sense_sampling_config_reg, dev_USB_MON.sensor_product_id,  dev_USB_MON.sensor_manufact_id,  dev_USB_MON.sensor_revision);
//         debugWriteLine(msg);

//         sprintf(msg, "Conf1: %s, res: %f, curr_sampl: %x,\r\n", dev_USB_MON.sensor_config_ch1.name, dev_USB_MON.sensor_config_ch1.current_sense_resistor_value, dev_USB_MON.sensor_config_ch1.current_sense_sampling_time_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_USB_MON.sensor_config_ch1.current_sense_sampling_average_reg, dev_USB_MON.sensor_config_ch1.current_sense_FSR_reg, dev_USB_MON.sensor_config_ch1.current_sense_FSC);
//         debugWriteLine(msg);
//         sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_USB_MON.sensor_config_ch1.source_voltage_sampling_time_reg, dev_USB_MON.sensor_config_ch1.source_voltage_sampling_average_reg, dev_USB_MON.sensor_config_ch1.source_voltage_FSV);
//         debugWriteLine(msg);
//         sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_USB_MON.sensor_config_ch1.power_sense_FSP, dev_USB_MON.sensor_config_ch1.current_sense_limit_reg, dev_USB_MON.sensor_config_ch1.source_voltage_limit_reg);
//         debugWriteLine(msg);

//         sprintf(msg, "Conf2: %s, res: %f, curr_sampl: %x,\r\n\r\n", dev_USB_MON.sensor_config_ch2.name, dev_USB_MON.sensor_config_ch2.current_sense_resistor_value, dev_USB_MON.sensor_config_ch2.current_sense_sampling_time_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_USB_MON.sensor_config_ch2.current_sense_sampling_average_reg, dev_USB_MON.sensor_config_ch2.current_sense_FSR_reg, dev_USB_MON.sensor_config_ch2.current_sense_FSC);
//         debugWriteLine(msg);
//         sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_USB_MON.sensor_config_ch2.source_voltage_sampling_time_reg, dev_USB_MON.sensor_config_ch2.source_voltage_sampling_average_reg, dev_USB_MON.sensor_config_ch2.source_voltage_FSV);
//         debugWriteLine(msg);
//         sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_USB_MON.sensor_config_ch2.power_sense_FSP, dev_USB_MON.sensor_config_ch2.current_sense_limit_reg, dev_USB_MON.sensor_config_ch2.source_voltage_limit_reg);
//         debugWriteLine(msg);

//         sprintf(msg, "CH1 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_USB_MON.ch1_readings.v_sense_voltage_reg, dev_USB_MON.ch1_readings.v_source_voltage_reg, dev_USB_MON.ch1_readings.power_ratio_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n", dev_USB_MON.ch1_readings.res_CURRENT, dev_USB_MON.ch1_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch1_readings.res_POWER, dev_USB_MON.ch1_readings.res_SENSE_VOLTAGE);
//         debugWriteLine(msg);

//         sprintf(msg, "CH2 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_USB_MON.ch2_readings.v_sense_voltage_reg, dev_USB_MON.ch2_readings.v_source_voltage_reg, dev_USB_MON.ch2_readings.power_ratio_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n\r\n\r\n", dev_USB_MON.ch2_readings.res_CURRENT, dev_USB_MON.ch2_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch2_readings.res_POWER, dev_USB_MON.ch2_readings.res_SENSE_VOLTAGE);
//         debugWriteLine(msg);
// }

// void print_FPGA_VCC(void)
// {
//         char msg[512];
//         sprintf(msg, "Name: %s, addr: %x, channels: %x\r\n", dev_FPGA_VCC.name,  dev_FPGA_VCC.sensor_address,  dev_FPGA_VCC.channels); 
//         debugWriteLine(msg);
//         sprintf(msg, "conf_reg: %x, conv_rate: %x, oneshot: %x,\r\n",  dev_FPGA_VCC.configuration_reg,  dev_FPGA_VCC.conversion_rate_reg,  dev_FPGA_VCC.one_shot_reg); 
//         debugWriteLine(msg);
//         sprintf(msg, "mask: %x, high_l: %x, low_l: %x, source_sample: %x,\r\n", dev_FPGA_VCC.channel_mask_reg,  dev_FPGA_VCC.high_limit_status_reg,  dev_FPGA_VCC.low_limit_status_reg,  dev_FPGA_VCC.source_voltage_sampling_config_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "sense_sample1: %x, sense_sample2: %x, id: %x, man: %x, rev: %x\r\n\r\n", dev_FPGA_VCC.ch1_current_sense_sampling_config_reg,  dev_FPGA_VCC.ch2_current_sense_sampling_config_reg, dev_FPGA_VCC.sensor_product_id,  dev_FPGA_VCC.sensor_manufact_id,  dev_FPGA_VCC.sensor_revision);
//         debugWriteLine(msg);

//         sprintf(msg, "Conf1: %s, res: %f, curr_sampl: %x,\r\n", dev_FPGA_VCC.sensor_config_ch1.name, dev_FPGA_VCC.sensor_config_ch1.current_sense_resistor_value, dev_FPGA_VCC.sensor_config_ch1.current_sense_sampling_time_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_FPGA_VCC.sensor_config_ch1.current_sense_sampling_average_reg, dev_FPGA_VCC.sensor_config_ch1.current_sense_FSR_reg, dev_FPGA_VCC.sensor_config_ch1.current_sense_FSC);
//         debugWriteLine(msg);
//         sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_FPGA_VCC.sensor_config_ch1.source_voltage_sampling_time_reg, dev_FPGA_VCC.sensor_config_ch1.source_voltage_sampling_average_reg, dev_FPGA_VCC.sensor_config_ch1.source_voltage_FSV);
//         debugWriteLine(msg);
//         sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_FPGA_VCC.sensor_config_ch1.power_sense_FSP, dev_FPGA_VCC.sensor_config_ch1.current_sense_limit_reg, dev_FPGA_VCC.sensor_config_ch1.source_voltage_limit_reg);
//         debugWriteLine(msg);

//         sprintf(msg, "Conf2: %s, res: %f, curr_sampl: %x,\r\n\r\n", dev_FPGA_VCC.sensor_config_ch2.name, dev_FPGA_VCC.sensor_config_ch2.current_sense_resistor_value, dev_FPGA_VCC.sensor_config_ch2.current_sense_sampling_time_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_FPGA_VCC.sensor_config_ch2.current_sense_sampling_average_reg, dev_FPGA_VCC.sensor_config_ch2.current_sense_FSR_reg, dev_FPGA_VCC.sensor_config_ch2.current_sense_FSC);
//         debugWriteLine(msg);
//         sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_FPGA_VCC.sensor_config_ch2.source_voltage_sampling_time_reg, dev_FPGA_VCC.sensor_config_ch2.source_voltage_sampling_average_reg, dev_FPGA_VCC.sensor_config_ch2.source_voltage_FSV);
//         debugWriteLine(msg);
//         sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_FPGA_VCC.sensor_config_ch2.power_sense_FSP, dev_FPGA_VCC.sensor_config_ch2.current_sense_limit_reg, dev_FPGA_VCC.sensor_config_ch2.source_voltage_limit_reg);
//         debugWriteLine(msg);

//         sprintf(msg, "CH1 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_FPGA_VCC.ch1_readings.v_sense_voltage_reg, dev_FPGA_VCC.ch1_readings.v_source_voltage_reg, dev_FPGA_VCC.ch1_readings.power_ratio_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n", dev_FPGA_VCC.ch1_readings.res_CURRENT, dev_FPGA_VCC.ch1_readings.res_SOURCE_VOLTAGE, dev_FPGA_VCC.ch1_readings.res_POWER, dev_FPGA_VCC.ch1_readings.res_SENSE_VOLTAGE);
//         debugWriteLine(msg);

//         sprintf(msg, "CH2 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_FPGA_VCC.ch2_readings.v_sense_voltage_reg, dev_FPGA_VCC.ch2_readings.v_source_voltage_reg, dev_FPGA_VCC.ch2_readings.power_ratio_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n\r\n\r\n", dev_FPGA_VCC.ch2_readings.res_CURRENT, dev_FPGA_VCC.ch2_readings.res_SOURCE_VOLTAGE, dev_FPGA_VCC.ch2_readings.res_POWER, dev_FPGA_VCC.ch2_readings.res_SENSE_VOLTAGE);
//         debugWriteLine(msg);
// }

// void print_WIREL_MCU(void)
// {
//         char msg[512];
//         sprintf(msg, "Name: %s, addr: %x, channels: %x\r\n", dev_WIREL_MCU.name,  dev_WIREL_MCU.sensor_address,  dev_WIREL_MCU.channels); 
//         debugWriteLine(msg);
//         sprintf(msg, "conf_reg: %x, conv_rate: %x, oneshot: %x,\r\n",  dev_WIREL_MCU.configuration_reg,  dev_WIREL_MCU.conversion_rate_reg,  dev_WIREL_MCU.one_shot_reg); 
//         debugWriteLine(msg);
//         sprintf(msg, "mask: %x, high_l: %x, low_l: %x, source_sample: %x,\r\n", dev_WIREL_MCU.channel_mask_reg,  dev_WIREL_MCU.high_limit_status_reg,  dev_WIREL_MCU.low_limit_status_reg,  dev_WIREL_MCU.source_voltage_sampling_config_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "sense_sample1: %x, sense_sample2: %x, id: %x, man: %x, rev: %x\r\n\r\n", dev_WIREL_MCU.ch1_current_sense_sampling_config_reg,  dev_WIREL_MCU.ch2_current_sense_sampling_config_reg, dev_WIREL_MCU.sensor_product_id,  dev_WIREL_MCU.sensor_manufact_id,  dev_WIREL_MCU.sensor_revision);
//         debugWriteLine(msg);

//         sprintf(msg, "Conf1: %s, res: %f, curr_sampl: %x,\r\n", dev_WIREL_MCU.sensor_config_ch1.name, dev_WIREL_MCU.sensor_config_ch1.current_sense_resistor_value, dev_WIREL_MCU.sensor_config_ch1.current_sense_sampling_time_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_WIREL_MCU.sensor_config_ch1.current_sense_sampling_average_reg, dev_WIREL_MCU.sensor_config_ch1.current_sense_FSR_reg, dev_WIREL_MCU.sensor_config_ch1.current_sense_FSC);
//         debugWriteLine(msg);
//         sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_WIREL_MCU.sensor_config_ch1.source_voltage_sampling_time_reg, dev_WIREL_MCU.sensor_config_ch1.source_voltage_sampling_average_reg, dev_WIREL_MCU.sensor_config_ch1.source_voltage_FSV);
//         debugWriteLine(msg);
//         sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_WIREL_MCU.sensor_config_ch1.power_sense_FSP, dev_WIREL_MCU.sensor_config_ch1.current_sense_limit_reg, dev_WIREL_MCU.sensor_config_ch1.source_voltage_limit_reg);
//         debugWriteLine(msg);

//         sprintf(msg, "Conf2: %s, res: %f, curr_sampl: %x,\r\n\r\n", dev_WIREL_MCU.sensor_config_ch2.name, dev_WIREL_MCU.sensor_config_ch2.current_sense_resistor_value, dev_WIREL_MCU.sensor_config_ch2.current_sense_sampling_time_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_WIREL_MCU.sensor_config_ch2.current_sense_sampling_average_reg, dev_WIREL_MCU.sensor_config_ch2.current_sense_FSR_reg, dev_WIREL_MCU.sensor_config_ch2.current_sense_FSC);
//         debugWriteLine(msg);
//         sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_WIREL_MCU.sensor_config_ch2.source_voltage_sampling_time_reg, dev_WIREL_MCU.sensor_config_ch2.source_voltage_sampling_average_reg, dev_WIREL_MCU.sensor_config_ch2.source_voltage_FSV);
//         debugWriteLine(msg);
//         sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_WIREL_MCU.sensor_config_ch2.power_sense_FSP, dev_WIREL_MCU.sensor_config_ch2.current_sense_limit_reg, dev_WIREL_MCU.sensor_config_ch2.source_voltage_limit_reg);
//         debugWriteLine(msg);

//         sprintf(msg, "CH1 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_WIREL_MCU.ch1_readings.v_sense_voltage_reg, dev_WIREL_MCU.ch1_readings.v_source_voltage_reg, dev_WIREL_MCU.ch1_readings.power_ratio_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n", dev_WIREL_MCU.ch1_readings.res_CURRENT, dev_WIREL_MCU.ch1_readings.res_SOURCE_VOLTAGE, dev_WIREL_MCU.ch1_readings.res_POWER, dev_WIREL_MCU.ch1_readings.res_SENSE_VOLTAGE);
//         debugWriteLine(msg);

//         sprintf(msg, "CH2 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_WIREL_MCU.ch2_readings.v_sense_voltage_reg, dev_WIREL_MCU.ch2_readings.v_source_voltage_reg, dev_WIREL_MCU.ch2_readings.power_ratio_reg);
//         debugWriteLine(msg);
//         sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n\r\n\r\n", dev_WIREL_MCU.ch2_readings.res_CURRENT, dev_WIREL_MCU.ch2_readings.res_SOURCE_VOLTAGE, dev_WIREL_MCU.ch2_readings.res_POWER, dev_WIREL_MCU.ch2_readings.res_SENSE_VOLTAGE);
//         debugWriteLine(msg);
// }