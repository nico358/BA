#include <stdio.h>
#include <stdint.h>
// #include "lib/PAC1720_driver/PAC1720_definitions.h"
// #include "lib/PAC1720_driver/PAC1720_driver.h"

// static struct PAC1720_device dev;
// static struct PAC1720_channel_config conf;

int main(void){
    char msg[100];
    // float res;
    // uint16_t reg = 0b0110100110000000;
    // uint16_t tmp = (reg >> 4);
    // res = (reg >> 4);
    // sprintf(msg, "val is: %x, dec: %d, float: %f\n", tmp, tmp, res);
    uint8_t t = 0b01010100;
    uint8_t *ptr = &t;
    uint8_t res = ~(*ptr);
    // uint8_t res = ~t;
    uint8_t x = res + 0x01;
    float f = (float) x;
    float z = -f;

    sprintf(msg, "val is: %x, inv: %x, +1: %x, float: %f, neg float: %f\n", t, res, x, f, z);
    printf(msg);

    
    



}

// //Test bitpattern in byte and print
// 	void Test_Bits_In_Byte(uint8_t* byte)
// 	{
// 		if(*byte & 0x80){
// 			send_bit(1);
// 			}else{
// 			send_bit(0);
// 		}
// 		if(*byte & 0x40){
// 			send_bit(1);
// 			}else{
// 			send_bit(0);
// 		}
// 		if(*byte & 0x20){
// 			send_bit(1);
// 			}else{
// 			send_bit(0);
// 		}
// 		if(*byte & 0x10){
// 			send_bit(1);
// 			}else{
// 			send_bit(0);
// 		}
// 		if(*byte & 0x08){
// 			send_bit(1);
// 			}else{
// 			send_bit(0);
// 		}
// 		if(*byte & 0x04){
// 			send_bit(1);
// 			}else{
// 			send_bit(0);
// 		}
// 		if(*byte & 0x02){
// 			send_bit(1);
// 			}else{
// 			send_bit(0);
// 		}
// 		if(*byte & 0x01){
// 			send_bit(1);
// 			}else{
// 			send_bit(0);
// 		}
// 	}

// //Test bitpattern in two bytes
// 	void Test_Bits_In_DoubleByte(uint16_t* doublebyte)
// 	{
// 		uint8_t lsb, msb;
// 		uint16_t tmp = *doublebyte;
// 		lsb = tmp;
// 		msb = (tmp >> 8);
// 		Test_Bits_In_Byte(&msb);
// 		Test_Bits_In_Byte(&lsb);
// 	}
	
// //Test bitpattern in four bytes
// 	void Test_Bits_In_Integer(uint32_t* quadbyte)
// 	{
// 		uint16_t lshex, mshex;
// 		uint32_t tmp = *quadbyte;
// 		lshex = tmp;
// 		mshex = (tmp >> 16);
// 		Test_Bits_In_DoubleByte(&mshex);
// 		Test_Bits_In_DoubleByte(&lshex);
// 	}

