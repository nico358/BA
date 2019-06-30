#include "include/currentSenseApp.h"
#include <stdio.h>
#include <string.h>

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

int8_t init_platform(void);
void print_error(uint8_t res);


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
            ext_delay_func(500);
        }
    }
    
    return 0;
}

int8_t init_platform(void)
{
    debugInit(NULL);
    i2c_init();
    // external_fieldbus_interface.init();
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