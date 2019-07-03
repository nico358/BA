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
void debug_meas_PAC1720(struct PAC1720_meas_internal *meas);
void debug_ch_PAC1720(struct PAC1720_CH_config *conf);

/***************************************** Function prototypes ***************************/
int8_t  init_platform(void);
void    check_user_input(void);
void    set_state(void);
void    print_error(uint8_t res);

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
            sprintf(msg, "In mode 2\r\n", res);
            debugWriteLine(msg);
            external_delay_function(500);
        }
        debug_PAC1720(&dev_USB_MON);

    }
    
    return 0;
}


int8_t init_platform(void)
{
    uint8_t res = PAC1720_OK;

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
        set_state();
    }
}

void set_state(void)
{
    uint8_t data = debugGetChar();
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

void print_error(uint8_t res){
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

    debug_ch(dev);
    debug_meas(dev);
    debugWriteLine("}\r\n\r\n\r\n");
}

void debug_PAC1720(struct PAC1720_device * dev){
    // char msg[512];
    // sprintf(msg, "Name: %s, addr: %x, channels: %x\r\n", dev->DEV_name_opt, dev->DEV_sensor_address, dev->DEV_channels);
    // debugWriteLine(msg);
    // sprintf(msg, "conf_reg: %x, conv_rate: %x, oneshot: %x,\r\n", dev->DEV_configuration_reg, dev->DEV_conversion_rate_reg, dev->DEV_one_shot_reg);
    // debugWriteLine(msg);
    // sprintf(msg, "mask: %x, high_l: %x, low_l: %x, source_sample: %x,\r\n", dev->DEV_mask_reg, dev_USB_MON.high_limit_status_reg, dev_USB_MON.low_limit_status_reg, dev_USB_MON.source_voltage_sampling_config_reg);
    // debugWriteLine(msg);
    // sprintf(msg, "sense_sample1: %x, sense_sample2: %x\r\n\r\n", dev_USB_MON.ch1_current_sense_sampling_config_reg, dev_USB_MON.ch2_current_sense_sampling_config_reg);
    // debugWriteLine(msg);
    // sprintf(msg, "id: %x, man: %x, rev: %x\r\n\r\n", sensor_product_id, dev_USB_MON.sensor_manufact_id, dev_USB_MON.sensor_revision);
    // debugWriteLine(msg);
}

// void debug_ch_PAC1720(struct PAC1720_CH_config *conf){
    // char msg[512];
//     sprintf(msg, "Conf1: %s, res: %f, curr_sampl: %x,\r\n", dev_USB_MON.sensor_config_ch1.name, dev_USB_MON.sensor_config_ch1.current_sense_resistor_value, dev_USB_MON.sensor_config_ch1.current_sense_sampling_time_reg);
//     debugWriteLine(msg);
//     sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_USB_MON.sensor_config_ch1.current_sense_sampling_average_reg, dev_USB_MON.sensor_config_ch1.current_sense_FSR_reg, dev_USB_MON.sensor_config_ch1.current_sense_FSC);
//     debugWriteLine(msg);
//     sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_USB_MON.sensor_config_ch1.source_voltage_sampling_time_reg, dev_USB_MON.sensor_config_ch1.source_voltage_sampling_average_reg, dev_USB_MON.sensor_config_ch1.source_voltage_FSV);
//     debugWriteLine(msg);
//     sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_USB_MON.sensor_config_ch1.power_sense_FSP, dev_USB_MON.sensor_config_ch1.current_sense_limit_reg, dev_USB_MON.sensor_config_ch1.source_voltage_limit_reg);
//     debugWriteLine(msg);
// }

// void debug_meas_PAC1720(struct PAC1720_meas_internal *meas){
    // char msg[512];
//     sprintf(msg, "CH1 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_USB_MON.ch1_readings.v_sense_voltage_reg, dev_USB_MON.ch1_readings.v_source_voltage_reg, dev_USB_MON.ch1_readings.power_ratio_reg);
//     debugWriteLine(msg);
//     sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n", dev_USB_MON.ch1_readings.res_CURRENT, dev_USB_MON.ch1_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch1_readings.res_POWER, dev_USB_MON.ch1_readings.res_SENSE_VOLTAGE);
//     debugWriteLine(msg);
// }