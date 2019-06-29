#include "include/currentSenseApp.h"
#include <stdio.h>
#include <string.h>

int8_t init_platform(void);
void print_error(uint8_t res);
void print_USB_MON(void);
void print_FPGA_VCC(void); 
void print_WIREL_MCU(void);
void print_measurements(void);


struct PAC1720_device                    dev_USB_MON;
char *name_USB_MON                       = "USB_MON";
char *name_CH1_USB_MON                   = "USB_VCC";
char *name_CH2_USB_MON                   = "MON_VCC";
const uint8_t addr_USB_MON               = 0x4D;
const float resistance_CH1_USB_MON       = 0.15f;
const float resistance_CH2_USB_MON       = 0.8f;
const ACTIVE_CHANNELS channels_USB_MON   = BOTH_CHANNELS;

struct PAC1720_device                    dev_FPGA_VCC;
char *name_FPGA_VCC                      = "FPGA_VCC";
char *name_CH1_FPGA_VCC                  = "FPGA_VCCINT_MON";
char *name_CH2_FPGA_VCC                  = "FPGA_VCCAUX_MON";
const uint8_t addr_FPGA_VCC              = 0x4F;
const float resistance_CH1_FPGA_VCC      = 0.8f;
const float resistance_CH2_FPGA_VCC      = 0.8f;
const ACTIVE_CHANNELS channels_FPGA_VCC  = BOTH_CHANNELS;

struct PAC1720_device                    dev_WIREL_MCU;
char *name_WIREL_MCU                     = "WIREL_MCU";
char *name_CH1_WIREL_MCU                 = "WIRELESS_VCC";
char *name_CH2_WIREL_MCU                 = "MCU_VCC";
const uint8_t addr_WIREL_MCU             = 0x29;
const float resistance_CH1_WIREL_MCU     = 0.8f;
const float resistance_CH2_WIREL_MCU     = 0.8f;
const ACTIVE_CHANNELS channels_WIREL_MCU = BOTH_CHANNELS;


struct BUS_INTERFACE_I2C i2c_interface = {
    .init       = &i2c_init,
    .stop       = &i2c_stop,
    .start      = &i2c_start,
    .repStart   = &i2c_rep_start,
    .startWait  = &i2c_start_wait,
    .write      = &i2c_write,
    .readAck    = &i2c_readAck,
    .readNak    = &i2c_readNak
};

user_delay_fptr ext_delay_func = &user_delay_ms;


int main(void)
{
    int8_t res = init_platform();

    if(res != PAC1720_OK) print_error(res);


    char msg[64];
    uint8_t state = 1;

    while(state){

        debugReadChar();
        if(debugReadCharAvailable())
        {
            uint8_t data = debugGetChar();
            switch(data)
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

        if(state == 2)
        {
            print_measurements();
            ext_delay_func(500);
        }
    }
    
    return 0;
}

int8_t init_platform(void)
{
    debugInit(NULL);
    i2c_interface.init();

    int8_t res = PAC1720_OK;
    res = adapter_init_PAC1720(&dev_USB_MON, name_USB_MON, name_CH1_USB_MON, name_CH2_USB_MON, &i2c_interface, ext_delay_func, addr_USB_MON, resistance_CH1_USB_MON, resistance_CH2_USB_MON, channels_USB_MON);
    if(res != PAC1720_OK) return res;
    res = adapter_init_PAC1720(&dev_FPGA_VCC, name_FPGA_VCC, name_CH1_FPGA_VCC, name_CH2_FPGA_VCC, &i2c_interface, ext_delay_func , addr_FPGA_VCC, resistance_CH1_FPGA_VCC, resistance_CH2_FPGA_VCC, channels_FPGA_VCC);
    if(res != PAC1720_OK) return res;
    return adapter_init_PAC1720(&dev_WIREL_MCU, name_WIREL_MCU, name_CH1_WIREL_MCU, name_CH2_WIREL_MCU, &i2c_interface, ext_delay_func, addr_WIREL_MCU, resistance_CH1_WIREL_MCU, resistance_CH2_WIREL_MCU, channels_WIREL_MCU);
}

void print_measurements(void)
{
    char msg[256];
    get_measurements(&dev_USB_MON);
    get_measurements(&dev_FPGA_VCC);
    get_measurements(&dev_WIREL_MCU);

    debugWriteLine("{\r\n");
    sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_USB_MON.sensor_config_ch1.name, dev_USB_MON.ch1_readings.res_CURRENT, dev_USB_MON.ch1_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch1_readings.res_POWER);
    debugWriteLine(msg);
    sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_USB_MON.sensor_config_ch2.name, dev_USB_MON.ch2_readings.res_CURRENT, dev_USB_MON.ch2_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch2_readings.res_POWER);
    debugWriteLine(msg);

    sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_FPGA_VCC.sensor_config_ch1.name, dev_FPGA_VCC.ch1_readings.res_CURRENT, dev_FPGA_VCC.ch1_readings.res_SOURCE_VOLTAGE, dev_FPGA_VCC.ch1_readings.res_POWER);
    debugWriteLine(msg);
    sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_FPGA_VCC.sensor_config_ch2.name, dev_FPGA_VCC.ch2_readings.res_CURRENT, dev_FPGA_VCC.ch2_readings.res_SOURCE_VOLTAGE, dev_FPGA_VCC.ch2_readings.res_POWER);
    debugWriteLine(msg);

    sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_WIREL_MCU.sensor_config_ch1.name, dev_WIREL_MCU.ch1_readings.res_CURRENT, dev_WIREL_MCU.ch1_readings.res_SOURCE_VOLTAGE, dev_WIREL_MCU.ch1_readings.res_POWER);
    debugWriteLine(msg);
    sprintf(msg, "[%s: current %fA voltage %fV power %fW]\r\n", dev_WIREL_MCU.sensor_config_ch2.name, dev_WIREL_MCU.ch2_readings.res_CURRENT, dev_WIREL_MCU.ch2_readings.res_SOURCE_VOLTAGE, dev_WIREL_MCU.ch2_readings.res_POWER);
    debugWriteLine(msg);
    debugWriteLine("}\r\n\r\n\r\n");
}

void print_USB_MON(void){
        char msg[512];
        sprintf(msg, "Name: %s, addr: %x, channels: %x\r\n", dev_USB_MON.name,  dev_USB_MON.sensor_address,  dev_USB_MON.channels); 
        debugWriteLine(msg);
        sprintf(msg, "conf_reg: %x, conv_rate: %x, oneshot: %x,\r\n",  dev_USB_MON.configuration_reg,  dev_USB_MON.conversion_rate_reg,  dev_USB_MON.one_shot_reg); 
        debugWriteLine(msg);
        sprintf(msg, "mask: %x, high_l: %x, low_l: %x, source_sample: %x,\r\n", dev_USB_MON.channel_mask_reg,  dev_USB_MON.high_limit_status_reg,  dev_USB_MON.low_limit_status_reg,  dev_USB_MON.source_voltage_sampling_config_reg);
        debugWriteLine(msg);
        sprintf(msg, "sense_sample1: %x, sense_sample2: %x, id: %x, man: %x, rev: %x\r\n\r\n", dev_USB_MON.ch1_current_sense_sampling_config_reg,  dev_USB_MON.ch2_current_sense_sampling_config_reg, dev_USB_MON.sensor_product_id,  dev_USB_MON.sensor_manufact_id,  dev_USB_MON.sensor_revision);
        debugWriteLine(msg);

        sprintf(msg, "Conf1: %s, res: %f, curr_sampl: %x,\r\n", dev_USB_MON.sensor_config_ch1.name, dev_USB_MON.sensor_config_ch1.current_sense_resistor_value, dev_USB_MON.sensor_config_ch1.current_sense_sampling_time_reg);
        debugWriteLine(msg);
        sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_USB_MON.sensor_config_ch1.current_sense_sampling_average_reg, dev_USB_MON.sensor_config_ch1.current_sense_FSR_reg, dev_USB_MON.sensor_config_ch1.current_sense_FSC);
        debugWriteLine(msg);
        sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_USB_MON.sensor_config_ch1.source_voltage_sampling_time_reg, dev_USB_MON.sensor_config_ch1.source_voltage_sampling_average_reg, dev_USB_MON.sensor_config_ch1.source_voltage_FSV);
        debugWriteLine(msg);
        sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_USB_MON.sensor_config_ch1.power_sense_FSP, dev_USB_MON.sensor_config_ch1.current_sense_limit_reg, dev_USB_MON.sensor_config_ch1.source_voltage_limit_reg);
        debugWriteLine(msg);

        sprintf(msg, "Conf2: %s, res: %f, curr_sampl: %x,\r\n\r\n", dev_USB_MON.sensor_config_ch2.name, dev_USB_MON.sensor_config_ch2.current_sense_resistor_value, dev_USB_MON.sensor_config_ch2.current_sense_sampling_time_reg);
        debugWriteLine(msg);
        sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_USB_MON.sensor_config_ch2.current_sense_sampling_average_reg, dev_USB_MON.sensor_config_ch2.current_sense_FSR_reg, dev_USB_MON.sensor_config_ch2.current_sense_FSC);
        debugWriteLine(msg);
        sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_USB_MON.sensor_config_ch2.source_voltage_sampling_time_reg, dev_USB_MON.sensor_config_ch2.source_voltage_sampling_average_reg, dev_USB_MON.sensor_config_ch2.source_voltage_FSV);
        debugWriteLine(msg);
        sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_USB_MON.sensor_config_ch2.power_sense_FSP, dev_USB_MON.sensor_config_ch2.current_sense_limit_reg, dev_USB_MON.sensor_config_ch2.source_voltage_limit_reg);
        debugWriteLine(msg);

        sprintf(msg, "CH1 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_USB_MON.ch1_readings.v_sense_voltage_reg, dev_USB_MON.ch1_readings.v_source_voltage_reg, dev_USB_MON.ch1_readings.power_ratio_reg);
        debugWriteLine(msg);
        sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n", dev_USB_MON.ch1_readings.res_CURRENT, dev_USB_MON.ch1_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch1_readings.res_POWER, dev_USB_MON.ch1_readings.res_SENSE_VOLTAGE);
        debugWriteLine(msg);

        sprintf(msg, "CH2 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_USB_MON.ch2_readings.v_sense_voltage_reg, dev_USB_MON.ch2_readings.v_source_voltage_reg, dev_USB_MON.ch2_readings.power_ratio_reg);
        debugWriteLine(msg);
        sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n\r\n\r\n", dev_USB_MON.ch2_readings.res_CURRENT, dev_USB_MON.ch2_readings.res_SOURCE_VOLTAGE, dev_USB_MON.ch2_readings.res_POWER, dev_USB_MON.ch2_readings.res_SENSE_VOLTAGE);
        debugWriteLine(msg);
}

void print_FPGA_VCC(void)
{
        char msg[512];
        sprintf(msg, "Name: %s, addr: %x, channels: %x\r\n", dev_FPGA_VCC.name,  dev_FPGA_VCC.sensor_address,  dev_FPGA_VCC.channels); 
        debugWriteLine(msg);
        sprintf(msg, "conf_reg: %x, conv_rate: %x, oneshot: %x,\r\n",  dev_FPGA_VCC.configuration_reg,  dev_FPGA_VCC.conversion_rate_reg,  dev_FPGA_VCC.one_shot_reg); 
        debugWriteLine(msg);
        sprintf(msg, "mask: %x, high_l: %x, low_l: %x, source_sample: %x,\r\n", dev_FPGA_VCC.channel_mask_reg,  dev_FPGA_VCC.high_limit_status_reg,  dev_FPGA_VCC.low_limit_status_reg,  dev_FPGA_VCC.source_voltage_sampling_config_reg);
        debugWriteLine(msg);
        sprintf(msg, "sense_sample1: %x, sense_sample2: %x, id: %x, man: %x, rev: %x\r\n\r\n", dev_FPGA_VCC.ch1_current_sense_sampling_config_reg,  dev_FPGA_VCC.ch2_current_sense_sampling_config_reg, dev_FPGA_VCC.sensor_product_id,  dev_FPGA_VCC.sensor_manufact_id,  dev_FPGA_VCC.sensor_revision);
        debugWriteLine(msg);

        sprintf(msg, "Conf1: %s, res: %f, curr_sampl: %x,\r\n", dev_FPGA_VCC.sensor_config_ch1.name, dev_FPGA_VCC.sensor_config_ch1.current_sense_resistor_value, dev_FPGA_VCC.sensor_config_ch1.current_sense_sampling_time_reg);
        debugWriteLine(msg);
        sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_FPGA_VCC.sensor_config_ch1.current_sense_sampling_average_reg, dev_FPGA_VCC.sensor_config_ch1.current_sense_FSR_reg, dev_FPGA_VCC.sensor_config_ch1.current_sense_FSC);
        debugWriteLine(msg);
        sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_FPGA_VCC.sensor_config_ch1.source_voltage_sampling_time_reg, dev_FPGA_VCC.sensor_config_ch1.source_voltage_sampling_average_reg, dev_FPGA_VCC.sensor_config_ch1.source_voltage_FSV);
        debugWriteLine(msg);
        sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_FPGA_VCC.sensor_config_ch1.power_sense_FSP, dev_FPGA_VCC.sensor_config_ch1.current_sense_limit_reg, dev_FPGA_VCC.sensor_config_ch1.source_voltage_limit_reg);
        debugWriteLine(msg);

        sprintf(msg, "Conf2: %s, res: %f, curr_sampl: %x,\r\n\r\n", dev_FPGA_VCC.sensor_config_ch2.name, dev_FPGA_VCC.sensor_config_ch2.current_sense_resistor_value, dev_FPGA_VCC.sensor_config_ch2.current_sense_sampling_time_reg);
        debugWriteLine(msg);
        sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_FPGA_VCC.sensor_config_ch2.current_sense_sampling_average_reg, dev_FPGA_VCC.sensor_config_ch2.current_sense_FSR_reg, dev_FPGA_VCC.sensor_config_ch2.current_sense_FSC);
        debugWriteLine(msg);
        sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_FPGA_VCC.sensor_config_ch2.source_voltage_sampling_time_reg, dev_FPGA_VCC.sensor_config_ch2.source_voltage_sampling_average_reg, dev_FPGA_VCC.sensor_config_ch2.source_voltage_FSV);
        debugWriteLine(msg);
        sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_FPGA_VCC.sensor_config_ch2.power_sense_FSP, dev_FPGA_VCC.sensor_config_ch2.current_sense_limit_reg, dev_FPGA_VCC.sensor_config_ch2.source_voltage_limit_reg);
        debugWriteLine(msg);

        sprintf(msg, "CH1 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_FPGA_VCC.ch1_readings.v_sense_voltage_reg, dev_FPGA_VCC.ch1_readings.v_source_voltage_reg, dev_FPGA_VCC.ch1_readings.power_ratio_reg);
        debugWriteLine(msg);
        sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n", dev_FPGA_VCC.ch1_readings.res_CURRENT, dev_FPGA_VCC.ch1_readings.res_SOURCE_VOLTAGE, dev_FPGA_VCC.ch1_readings.res_POWER, dev_FPGA_VCC.ch1_readings.res_SENSE_VOLTAGE);
        debugWriteLine(msg);

        sprintf(msg, "CH2 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_FPGA_VCC.ch2_readings.v_sense_voltage_reg, dev_FPGA_VCC.ch2_readings.v_source_voltage_reg, dev_FPGA_VCC.ch2_readings.power_ratio_reg);
        debugWriteLine(msg);
        sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n\r\n\r\n", dev_FPGA_VCC.ch2_readings.res_CURRENT, dev_FPGA_VCC.ch2_readings.res_SOURCE_VOLTAGE, dev_FPGA_VCC.ch2_readings.res_POWER, dev_FPGA_VCC.ch2_readings.res_SENSE_VOLTAGE);
        debugWriteLine(msg);
}

void print_WIREL_MCU(void)
{
        char msg[512];
        sprintf(msg, "Name: %s, addr: %x, channels: %x\r\n", dev_WIREL_MCU.name,  dev_WIREL_MCU.sensor_address,  dev_WIREL_MCU.channels); 
        debugWriteLine(msg);
        sprintf(msg, "conf_reg: %x, conv_rate: %x, oneshot: %x,\r\n",  dev_WIREL_MCU.configuration_reg,  dev_WIREL_MCU.conversion_rate_reg,  dev_WIREL_MCU.one_shot_reg); 
        debugWriteLine(msg);
        sprintf(msg, "mask: %x, high_l: %x, low_l: %x, source_sample: %x,\r\n", dev_WIREL_MCU.channel_mask_reg,  dev_WIREL_MCU.high_limit_status_reg,  dev_WIREL_MCU.low_limit_status_reg,  dev_WIREL_MCU.source_voltage_sampling_config_reg);
        debugWriteLine(msg);
        sprintf(msg, "sense_sample1: %x, sense_sample2: %x, id: %x, man: %x, rev: %x\r\n\r\n", dev_WIREL_MCU.ch1_current_sense_sampling_config_reg,  dev_WIREL_MCU.ch2_current_sense_sampling_config_reg, dev_WIREL_MCU.sensor_product_id,  dev_WIREL_MCU.sensor_manufact_id,  dev_WIREL_MCU.sensor_revision);
        debugWriteLine(msg);

        sprintf(msg, "Conf1: %s, res: %f, curr_sampl: %x,\r\n", dev_WIREL_MCU.sensor_config_ch1.name, dev_WIREL_MCU.sensor_config_ch1.current_sense_resistor_value, dev_WIREL_MCU.sensor_config_ch1.current_sense_sampling_time_reg);
        debugWriteLine(msg);
        sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_WIREL_MCU.sensor_config_ch1.current_sense_sampling_average_reg, dev_WIREL_MCU.sensor_config_ch1.current_sense_FSR_reg, dev_WIREL_MCU.sensor_config_ch1.current_sense_FSC);
        debugWriteLine(msg);
        sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_WIREL_MCU.sensor_config_ch1.source_voltage_sampling_time_reg, dev_WIREL_MCU.sensor_config_ch1.source_voltage_sampling_average_reg, dev_WIREL_MCU.sensor_config_ch1.source_voltage_FSV);
        debugWriteLine(msg);
        sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_WIREL_MCU.sensor_config_ch1.power_sense_FSP, dev_WIREL_MCU.sensor_config_ch1.current_sense_limit_reg, dev_WIREL_MCU.sensor_config_ch1.source_voltage_limit_reg);
        debugWriteLine(msg);

        sprintf(msg, "Conf2: %s, res: %f, curr_sampl: %x,\r\n\r\n", dev_WIREL_MCU.sensor_config_ch2.name, dev_WIREL_MCU.sensor_config_ch2.current_sense_resistor_value, dev_WIREL_MCU.sensor_config_ch2.current_sense_sampling_time_reg);
        debugWriteLine(msg);
        sprintf(msg, "curr_avrg: %x, FSR: %x, FSC: %f\r\n", dev_WIREL_MCU.sensor_config_ch2.current_sense_sampling_average_reg, dev_WIREL_MCU.sensor_config_ch2.current_sense_FSR_reg, dev_WIREL_MCU.sensor_config_ch2.current_sense_FSC);
        debugWriteLine(msg);
        sprintf(msg, "src_sampl: %x, src_avrg: %x, FSV: %f\r\n", dev_WIREL_MCU.sensor_config_ch2.source_voltage_sampling_time_reg, dev_WIREL_MCU.sensor_config_ch2.source_voltage_sampling_average_reg, dev_WIREL_MCU.sensor_config_ch2.source_voltage_FSV);
        debugWriteLine(msg);
        sprintf(msg, "FSP: %f, curr_lim: %x, srcvlt_lim: %x\r\n\r\n", dev_WIREL_MCU.sensor_config_ch2.power_sense_FSP, dev_WIREL_MCU.sensor_config_ch2.current_sense_limit_reg, dev_WIREL_MCU.sensor_config_ch2.source_voltage_limit_reg);
        debugWriteLine(msg);

        sprintf(msg, "CH1 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_WIREL_MCU.ch1_readings.v_sense_voltage_reg, dev_WIREL_MCU.ch1_readings.v_source_voltage_reg, dev_WIREL_MCU.ch1_readings.power_ratio_reg);
        debugWriteLine(msg);
        sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n", dev_WIREL_MCU.ch1_readings.res_CURRENT, dev_WIREL_MCU.ch1_readings.res_SOURCE_VOLTAGE, dev_WIREL_MCU.ch1_readings.res_POWER, dev_WIREL_MCU.ch1_readings.res_SENSE_VOLTAGE);
        debugWriteLine(msg);

        sprintf(msg, "CH2 sensevolt: %x, srcvolt: %x, pwrratio: %x\r\n", dev_WIREL_MCU.ch2_readings.v_sense_voltage_reg, dev_WIREL_MCU.ch2_readings.v_source_voltage_reg, dev_WIREL_MCU.ch2_readings.power_ratio_reg);
        debugWriteLine(msg);
        sprintf(msg, "current: %f, voltage: %f, power: %f, sensevoltage: %f\r\n\r\n\r\n\r\n", dev_WIREL_MCU.ch2_readings.res_CURRENT, dev_WIREL_MCU.ch2_readings.res_SOURCE_VOLTAGE, dev_WIREL_MCU.ch2_readings.res_POWER, dev_WIREL_MCU.ch2_readings.res_SENSE_VOLTAGE);
        debugWriteLine(msg);
}

void print_error(uint8_t res){
    for (;;)
    {
        char msg[64];
        sprintf(msg, "Failure while initializing: %d\r\n", res);
        debugWriteLine(msg);
        ext_delay_func(500);
    }
}