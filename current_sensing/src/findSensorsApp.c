#include "include/currentSenseApp.h"
#include <stdio.h>
#include <string.h>

/************************************** Dependencies to be injected ************************************/
/* Instantiate a bus interface */
struct BUS_INTERFACE i2c_interface = {
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
delay_function_ptr ext_delay_func = &user_delay_ms;

/*********************************************** Main ****************************************************/
int main(void)
{
    /* Init hardware */
    debugInit(NULL);
    i2c_interface.init();
    /* Result array */
    char addr[16] = {0};
    char msg[248];

    for(;;){
        /* Poll sensor addresses */
        uint8_t res = adapter_find_sensors(addr, &i2c_interface, ext_delay_func);
        sprintf(msg, "Found sensors: %d, ", res);
        /* Loop over array and print address if address found */
        for(uint8_t i = 0; i < SENSOR_ADDRESS_NUMBER; i++){
            if(addr[i]){
                sprintf(msg + strlen(msg), "found addr: [%x], ", addr[i]);
            }
        }
        /* Print count of found sensors */
        sprintf(msg + strlen(msg), "%s","\r\n");
        debugWriteLine(msg);

        ext_delay_func(1000);
    }

}
