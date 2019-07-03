#include "include/currentSenseApp.h"

/* Instanciate a field bus interface */
struct FIELD_BUS_INTERFACE external_fieldbus_interface = {
    /** Assign i2cmaster library to pointers */
    .init       = &i2c_init,
    .stop       = &i2c_stop,
    .start      = &i2c_start,
    .repStart   = &i2c_rep_start,
    .startWait  = &i2c_start_wait,
    .write      = &i2c_write,
    .readAck    = &i2c_readAck,
    .readNak    = &i2c_readNak
};

/** Assign user provided delay function to pointer */
delay_function_ptr external_delay_function = &user_delay_ms;

/********************************************Debug ******************************/
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

void print_measurements_PAC1720(struct PAC1720_device * dev);
void debug_PAC1720(struct PAC1720_device * dev);

/***************************************** Function prototypes ***************************/
int8_t  init_platform(void);
void    check_user_input(void);
void    set_state(uint8_t data);
void    print_error(int8_t res);

/***************************************** Main ******************************************/
/** User input controlled state */
uint8_t state = 1;

int main(void)
{   
    int8_t res = init_platform();

    if(res != PAC1720_OK) 
    {
        print_error(res);
    }

    char msg[64];

    while(state){

        check_user_input();

        if(state == 2)
        {  
            adapter_get_measurements_PAC1720(&dev_USB_MON);
            debug_PAC1720(&dev_USB_MON);
            adapter_get_measurements_PAC1720(&dev_FPGA_VCC);
            debug_PAC1720(&dev_FPGA_VCC);
            adapter_get_measurements_PAC1720(&dev_WIREL_MCU);
            debug_PAC1720(&dev_WIREL_MCU);
            
            external_delay_function(500);
        }

    }
    
    return 0;
}


int8_t init_platform(void)
{
    int8_t res = PAC1720_OK;

    debugInit(NULL);
    external_fieldbus_interface.init();
    adapter_init_peripherals(&external_fieldbus_interface, external_delay_function);

    res = adapter_init_PAC1720_from_field(&dev_USB_MON);
    if(res != PAC1720_OK) 
    {
        return res;
    }
    res = adapter_init_PAC1720_from_field(&dev_FPGA_VCC);
    if(res != PAC1720_OK)
    {
        return res;
    }
    return adapter_init_PAC1720_from_field(&dev_WIREL_MCU);
}

void check_user_input(void)
{
    debugReadChar();
    if (debugReadCharAvailable())
    {
        uint8_t data = debugGetChar();
        set_state(data);
    }
}

void set_state(uint8_t data)
{
    switch (data)
    {
    case 'C':
        state = 2;
        break;
    case 'q':
        state = 0;
        break;
    default:
        state = 1;
    }
}

void print_error(int8_t res){
    for (;;)
    {
        char msg[64];
        sprintf(msg, "Failure while initializing: %d\r\n", res);
        debugWriteLine(msg);
        external_delay_function(1000);
    }
}

void print_measurements_PAC1720(struct PAC1720_device * dev)
{
    char msg[256];

    debugWriteLine("{\r\n");
    sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev->DEV_CH1_conf.CH_name_opt, dev->DEV_CH1_measurements.CURRENT, dev->DEV_CH1_measurements.SOURCE_VOLTAGE, dev->DEV_CH1_measurements.POWER);
    debugWriteLine(msg);
    sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev->DEV_CH2_conf.CH_name_opt, dev->DEV_CH2_measurements.CURRENT, dev->DEV_CH2_measurements.SOURCE_VOLTAGE, dev->DEV_CH2_measurements.POWER);
    debugWriteLine(msg);
    debugWriteLine("}\r\n\r\n\r\n");
}

void debug_PAC1720(struct PAC1720_device * dev){
    char msg[512];
    if(dev->internal != NULL)
    {
        struct PAC1720_internal *dev_internal = dev->internal;
        if(dev->DEV_name_opt != NULL){
            sprintf(msg, "Name: %s\r\n", dev->DEV_name_opt);
            debugWriteLine(msg);
        }
        sprintf(msg, "addr: %x, conf_reg: %x, conv_rate_reg: %x, oneshot_reg: %x, mask_reg: %x\r\n\r\n", dev->DEV_sensor_address, dev->DEV_configuration_reg, dev->DEV_conversion_rate_reg, dev->DEV_one_shot_reg,  dev->DEV_mask_reg);
        debugWriteLine(msg);

        uint8_t high_lim_status_reg = 0;
        high_lim_status_reg |= dev->DEV_CH1_measurements.conversion_done << 7;
        high_lim_status_reg |= dev->DEV_CH2_measurements.conversion_done << 7;
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
        debugWriteLine(msg);

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
        debugWriteLine(msg);

        if(dev->DEV_CH1_measurements.meas_internal != NULL){
            struct PAC1720_meas_internal * internal = dev->DEV_CH1_measurements.meas_internal;
            sprintf(msg, "CH1 v_sense_voltage_reg: %x,  v_source_voltage_reg: %x, power_ratio_reg: %x\r\n", internal->v_sense_voltage_reg, internal->v_source_voltage_reg, internal->power_ratio_reg);
            debugWriteLine(msg);
            sprintf(msg, "CH1 SENSE_VOLTAGE: %f, CURRENT: %fA, SOURCE_VOLTAGE: %fV, POWER: %fW\r\n\r\n", dev->DEV_CH1_measurements.SENSE_VOLTAGE, dev->DEV_CH1_measurements.CURRENT, dev->DEV_CH1_measurements.SOURCE_VOLTAGE, dev->DEV_CH1_measurements.POWER);
            debugWriteLine(msg);
        }
        if(dev->DEV_CH2_measurements.meas_internal != NULL){
            struct PAC1720_meas_internal * internal = dev->DEV_CH2_measurements.meas_internal;
            sprintf(msg, "CH2 v_sense_voltage_reg: %x,  v_source_voltage_reg: %x, power_ratio_reg: %x\r\n", internal->v_sense_voltage_reg, internal->v_source_voltage_reg, internal->power_ratio_reg);
            debugWriteLine(msg);
            sprintf(msg, "CH2 SENSE_VOLTAGE: %f, CURRENT: %fA, SOURCE_VOLTAGE: %fV, POWER: %fW\r\n\r\n", dev->DEV_CH2_measurements.SENSE_VOLTAGE, dev->DEV_CH2_measurements.CURRENT, dev->DEV_CH2_measurements.SOURCE_VOLTAGE, dev->DEV_CH2_measurements.POWER);
            debugWriteLine(msg);
        }

        sprintf(msg, "CH1_current_sense_high_limit_reg: %x, CH2_current_sense_high_limit_reg: %x\r\n", dev->DEV_CH1_conf.CH_current_sense_high_limit_reg, dev->DEV_CH2_conf.CH_current_sense_high_limit_reg);
        debugWriteLine(msg);
        sprintf(msg, "CH1_current_sense_low_limit_reg: %x, CH2_current_sense_low_limit_reg: %x\r\n", dev->DEV_CH1_conf.CH_current_sense_low_limit_reg, dev->DEV_CH2_conf.CH_current_sense_low_limit_reg);
        debugWriteLine(msg);
        sprintf(msg, "CH1_source_voltage_high_limit_reg: %x, CH2_source_voltage_high_limit_reg: %x\r\n", dev->DEV_CH1_conf.CH_source_voltage_high_limit_reg, dev->DEV_CH2_conf.CH_source_voltage_high_limit_reg);
        debugWriteLine(msg);
        sprintf(msg, "CH1_source_voltage_low_limit_reg: %x, CH2_source_voltage_low_limit_reg: %x\r\n\r\n", dev->DEV_CH1_conf.CH_source_voltage_low_limit_reg, dev->DEV_CH2_conf.CH_source_voltage_low_limit_reg);
        debugWriteLine(msg);

        if(dev->DEV_CH1_conf.ch_internal != NULL)
        {
            struct PAC1720_ch_internal *internal = dev->DEV_CH1_conf.ch_internal;
            sprintf(msg, "Name: %s, Res: %f\r\n", dev->DEV_CH1_conf.CH_name_opt, dev->DEV_CH1_conf.CH_current_sense_resistor_value);
            debugWriteLine(msg);
            sprintf(msg, "FSC: %f, FSV: %f, FSP: %f\r\n\r\n", internal->current_sense_FSC, internal->source_voltage_FSV, internal->power_sense_FSP);
            debugWriteLine(msg);
            
        }
        if(dev->DEV_CH2_conf.ch_internal != NULL)
        {
            struct PAC1720_ch_internal *internal = dev->DEV_CH2_conf.ch_internal;
            sprintf(msg, "Name: %s, Res: %f\r\n", dev->DEV_CH2_conf.CH_name_opt, dev->DEV_CH2_conf.CH_current_sense_resistor_value);
            debugWriteLine(msg);
            sprintf(msg, "FSC: %f, FSV: %f, FSP: %f\r\n\r\n", internal->current_sense_FSC, internal->source_voltage_FSV, internal->power_sense_FSP);
            debugWriteLine(msg);
        }

        sprintf(msg, "id: %x, man: %x, rev: %x\r\n\r\n\r\n\r\n", dev_internal->sensor_product_id, dev_internal->sensor_manufact_id, dev_internal->sensor_revision);
        debugWriteLine(msg);
    }
}