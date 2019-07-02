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

/** Function prototypes */
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

    }
    
    return 0;
}


int8_t init_platform(void)
{
    uint8_t res = PAC1720_OK;

    debugInit(NULL);
    external_fieldbus_interface.init();
    adapter_init_peripherals(&external_fieldbus_interface, external_delay_function);

    res = adapter_init_PAC1720(&dev_USB_MON);
    if(res != PAC1720_OK) 
    {
        return res;
    }
    res = adapter_init_PAC1720(&dev_FPGA_VCC);
    if(res != PAC1720_OK)
    {
        return res;
    }
    return adapter_init_PAC1720(&dev_WIREL_MCU);
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