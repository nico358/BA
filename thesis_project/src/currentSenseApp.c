#include "include/currentSenseApp.h"
#include <stdio.h>
#include <string.h>

//USB_VCC (Rsense = 0.15Ohm), MON_VCC (Rsense = 0.8Ohm)					= 100Ohm => 1001_101 = 4D
//FPGA_VCCINT_MON (Rsense = 0.8Ohm), FPGA_VCCAUX_MON (Rsense = 0.8Ohm)	= 300Ohm => 1001_111 = 4F
//WIRELESS_VCC (Rsense = 0.8Ohm), MCU_VCC (Rsense = 0.8Ohm)				= 2k  	 => 0101_001 = 29
void init_platform(void);


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
    init_platform();

    char addr[16] = {0};
    char msg[248];

    for(;;){

        uint8_t res = adapter_find_sensors(&i2c_interface, ext_delay_func, addr);
        sprintf(msg, "Found sensors: %d, ", res);
        for(uint8_t i = 0; i < SENSOR_ADDRESS_NUMBER; i++){
            if(addr[i]){
                sprintf(msg + strlen(msg), "found addr: [%x], ", addr[i]);
            }
        }
        sprintf(msg + strlen(msg), "%s","\r\n");
        debugWriteLine(msg);

        ext_delay_func(1000);
    }

}

void init_platform(void)
{
    debugInit(NULL);
    i2c_interface.init();

    adapter_init_PAC1720(&dev_USB_MON, name_USB_MON, name_CH1_USB_MON, name_CH2_USB_MON, &i2c_interface, ext_delay_func, addr_USB_MON, resistance_CH1_USB_MON, resistance_CH2_USB_MON, channels_USB_MON);
    adapter_init_PAC1720(&dev_FPGA_VCC, name_FPGA_VCC, name_CH1_FPGA_VCC, name_CH2_FPGA_VCC, &i2c_interface, ext_delay_func , addr_FPGA_VCC, resistance_CH1_FPGA_VCC, resistance_CH2_FPGA_VCC, channels_FPGA_VCC);
    adapter_init_PAC1720(&dev_WIREL_MCU, name_WIREL_MCU, name_CH1_WIREL_MCU, name_CH2_WIREL_MCU, &i2c_interface, ext_delay_func, addr_WIREL_MCU, resistance_CH1_WIREL_MCU, resistance_CH2_WIREL_MCU, channels_WIREL_MCU);
}
