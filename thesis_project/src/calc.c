#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lib/PAC1720_driver/PAC1720_driver.h"


struct PAC1720_ch_internal
{
    /* Full Scale Current (FSC) */
	float 		current_sense_FSC;
    /* Full Scale Voltage (FSV) */
	float 		source_voltage_FSV;
	/* Full Scale Power (FSP)  */
	float 		power_sense_FSP;
};




int main(void){

struct PAC1720_device dev;
static struct PAC1720_ch_internal internal;

dev.DEV_CH1_conf.ch_internal = &internal;


char msg[128];
sprintf(msg, "%p = %p, %f, %f, %f\r\n", dev.DEV_CH1_conf.ch_internal, &internal, internal.current_sense_FSC, internal.power_sense_FSP, internal.source_voltage_FSV);
printf(msg);

}

