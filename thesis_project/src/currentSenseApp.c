#include "include/currentSenseApp.h"

/************************************** Dependencies to be injected ************************************/
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

/***************************************** Function prototypes *******************************************/
int8_t  init_platform(void);
void    tear_down_platform(void);
void    check_user_input(uint8_t *state);  
void    set_state(uint8_t data, uint8_t *state);
void    print_error(int8_t res);

/*********************************************** Main ****************************************************/

int main(void)
{   
    int8_t res = init_platform();
    if(res != PAC1720_OK) print_error(res);

    char msg[64];
    /** User input controlled state */
    uint8_t state = 1;

    while(state){

        check_user_input(&state);

        if(state == 2)
        {  
            adapter_get_measurements_PAC1720(&dev_USB_MON);
            print_measurements_PAC1720(&dev_USB_MON, &debugWriteLine);

            // debug_PAC1720(&dev_USB_MON, &debugWriteLine);
            // adapter_get_measurements_PAC1720(&dev_FPGA_VCC);
            // debug_PAC1720(&dev_FPGA_VCC, &debugWriteLine);
            // adapter_get_measurements_PAC1720(&dev_WIREL_MCU);
            // debug_PAC1720(&dev_WIREL_MCU, &debugWriteLine);
            
            // external_delay_function(500);
        }

    }
    tear_down_platform();
    return 0;
}


int8_t init_platform(void)
{
    int8_t res = PAC1720_OK;

    debugInit(NULL);
    external_fieldbus_interface.init();

    adapter_init_peripherals(&external_fieldbus_interface, external_delay_function);
    
    res = adapter_init_PAC1720_user_defined(&dev_USB_MON);
    if(res != PAC1720_OK) return res;

    // res = adapter_init_PAC1720_from_field(&dev_USB_MON);
    // if(res != PAC1720_OK) return res;
    // res = adapter_init_PAC1720_from_field(&dev_FPGA_VCC);
    // if(res != PAC1720_OK) return res;
    // return adapter_init_PAC1720_from_field(&dev_WIREL_MCU);
}

void tear_down_platform(void)
{
    adapter_destroy_PAC1720(&dev_USB_MON);
    adapter_destroy_PAC1720(&dev_FPGA_VCC);
    adapter_destroy_PAC1720(&dev_WIREL_MCU);
}

void check_user_input(uint8_t *state)
{
    debugReadChar();
    if (debugReadCharAvailable())
    {
        uint8_t data = debugGetChar();
        set_state(data, state);
    }
}

void set_state(uint8_t data, uint8_t *state)
{
    switch (data)
    {
    case 'C':
        *state = 2;
        break;
    case 'q':
        *state = 0;
        break;
    default:
        *state = 1;
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

