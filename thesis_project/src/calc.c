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

void interleave(uint8_t arr[3]);


int main(void){

uint8_t arr[3] = {0};
interleave(arr);

char msg[128];
sprintf(msg, "1: %x,  2: %x, 3: %x\r\n", arr[0], arr[1], arr[2]);
printf(msg);

}

void interleave(uint8_t arr[3]){
    uint8_t a = 0b00000011;
    uint8_t b = 0b00000001;
    uint8_t c = 0b00000010;
    arr[0] = a << 1;
    arr[0] = arr[0] | b << 3;
    arr[0] = arr[0] | c << 5;
    
}