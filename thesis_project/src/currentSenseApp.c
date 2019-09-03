#include "include/currentSenseApp.h"

/************************************** Dependencies to be injected ************************************/
/* Instantiate a bus interface */
struct BUS_INTERFACE external_bus_interface = {
    /** Assign i2cmaster library function addresses to members */
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
    /* Init the hardware, print error if fail */
    int8_t res = init_platform();
    if(res != PAC1720_OK) print_error(res);
    /* Debug string */
    char msg[64];
    /** User controlled state */
    uint8_t state = 2;
    /* Result of get_measurements */
    uint8_t meas_fail = 0;

    while(state){

        check_user_input(&state);
        /* Enter measurement mode, get measurements and print them in every loop */
        if(state > 2)
        {
            if(state == 3 || state == 6){
                meas_fail = adapter_get_measurements_fast_PAC1720(&dev_USB_MON);
                if(!meas_fail){
                    print_measurements_PAC1720(&dev_USB_MON, &debugWriteString, get_counter());
                    user_delay_ms(1);
                }
            }
            if(state == 4 || state == 6){
                meas_fail = adapter_get_measurements_fast_PAC1720(&dev_FPGA_VCC);
                if(!meas_fail)
                {
                    print_measurements_PAC1720(&dev_FPGA_VCC, &debugWriteString, get_counter());
                    // sprintf(msg, "%u\r\n",  get_counter());
                    // debugWriteLine(msg);
                    // reset_counter();
                    // debug_PAC1720(&dev_FPGA_VCC, &debugWriteString);
                    user_delay_ms(1);
                }
            }   
            if(state == 5 || state == 6){ 
                meas_fail = adapter_get_measurements_fast_PAC1720(&dev_WIREL_MCU);
                if(!meas_fail)
                {
                    print_measurements_PAC1720(&dev_WIREL_MCU, &debugWriteString, get_counter());
                    // debug_PAC1720(&dev_WIREL_MCU, &debugWriteString);
                    user_delay_ms(1);
                }
            }
        }
        /* Reset measurement counter when leaving measurement mode */
        if(state == 1){
            adapterResetMeasCounts(&dev_WIREL_MCU);
            adapterResetMeasCounts(&dev_FPGA_VCC);
            adapterResetMeasCounts(&dev_USB_MON);
            state = 2;
        }
    }
    /* End of program */
    debugWriteLine("End measurement\r\n");
    tear_down_platform();
    return 0;
}

/* Initialize hardware */
int8_t init_platform(void)
{
    int8_t res = PAC1720_OK;
    /* Init debug */
    debugInit(NULL);
    /* Init TWI */
    external_bus_interface.init();
    /* Init counter */
    counter_init();
    /* Inject bus communication and delay function pointer to adapter */
    adapter_init_peripherals(&external_bus_interface, external_delay_function);
    /* Configure sensors, struct instances are located in adapter */
    res = adapter_init_PAC1720_user_defined(&dev_USB_MON);
    if(res != PAC1720_OK) return res;
    res = adapter_init_PAC1720_user_defined(&dev_FPGA_VCC);
    if(res != PAC1720_OK) return res;
    res = adapter_init_PAC1720_user_defined(&dev_WIREL_MCU);
    return res;
}

/* Clean up */
void tear_down_platform(void)
{
    counter_stop();
    adapter_destroy_PAC1720(&dev_USB_MON);
    adapter_destroy_PAC1720(&dev_FPGA_VCC);
    adapter_destroy_PAC1720(&dev_WIREL_MCU);
}

/* Check if user sets another application state */
void check_user_input(uint8_t *state)
{
    debugReadChar();
    if (debugReadCharAvailable())
    {
        uint8_t data = debugGetChar();
        set_state(data, state);
    }
}

/* Switch state according to user input */
void set_state(uint8_t data, uint8_t *state)
{
    switch (data)
    {
    case 'A': // Monitor all
        *state = 6;
        reset_counter();
        break;
    case 'U': // USB monitoring
        *state = 3;
        reset_counter();
        break;
    case 'F': // FPGA monitoring
        *state = 4;
        reset_counter();
        break;
    case 'W': // Wireless monitoring
        *state = 5;
        reset_counter();
        break;
    case 'q': // Leave program
        *state = 0;
        break;
    default: // Reset measurement counters and loop without monitoring
        *state = 1;
    }
}

/* Print error in loop */
void print_error(int8_t res){
    for (;;)
    {
        char msg[64];
        sprintf(msg, "Failure while initializing: %d\r\n", res);
        debugWriteLine(msg);
        external_delay_function(1000);
    }
}
