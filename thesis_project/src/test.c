#include <stdio.h>
#include <stdint.h>
#include "lib/PAC1720_driver/PAC1720_driver.h"

typedef int8_t (*calculate_BUS_CURRENT) (const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings);
typedef float (*calculate_SENSED_VOLTAGE) (const uint16_t *v_sense_voltage_reg_ptr, const uint8_t *current_sense_sampling_time_reg_ptr);
typedef int8_t (*calculate_FSC) (struct PAC1720_channel_config *config_ptr);
typedef uint16_t (*twos_complement) (const uint16_t *complement);
typedef bool (*is_negative_value) (const uint16_t *value);
typedef uint16_t (*right_bit_shift) (const uint16_t *doublebyte, uint8_t shift);
typedef int8_t (*device_null_pointer_check) (const struct PAC1720_device *device_ptr);
typedef float (*calculate_BUS_VOLTAGE) (const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings);
typedef float (*calculate_SOURCE_VOLTAGE) (const uint16_t *v_source_voltage_reg_ptr, const uint8_t *source_voltage_sampling_time_reg_ptr);
typedef int8_t (*calculate_FSV) (struct PAC1720_channel_config *config_ptr);

calculate_BUS_CURRENT calculate_BUS_CURRENT_func;
calculate_SENSED_VOLTAGE calculate_SENSED_VOLTAGE_func;
calculate_FSC calculate_FSC_func;
twos_complement twos_complement_func;
is_negative_value is_negative_value_func;
right_bit_shift right_bit_shift_func;
device_null_pointer_check device_null_pointer_check_func;
calculate_BUS_VOLTAGE calculate_BUS_VOLTAGE_func;
calculate_SOURCE_VOLTAGE calculate_SOURCE_VOLTAGE_func;
calculate_FSV calculate_FSV_func;


void setUp(void) {
    const (**test_fptr_field)[7]        = (PAC1720_fptr*) get_TEST_FPTR_FIELD();
    calculate_BUS_CURRENT_func          = (calculate_BUS_CURRENT) test_fptr_field[0];
    calculate_SENSED_VOLTAGE_func       = (calculate_SENSED_VOLTAGE) test_fptr_field[1];
    calculate_FSC_func                  = (calculate_FSC) test_fptr_field[2];
    twos_complement_func                = (twos_complement) test_fptr_field[3];
    is_negative_value_func              = (is_negative_value) test_fptr_field[4];
    right_bit_shift_func                = (right_bit_shift) test_fptr_field[5];
    device_null_pointer_check_func      = (device_null_pointer_check) test_fptr_field[6];
    calculate_BUS_VOLTAGE_func          = (calculate_BUS_VOLTAGE) test_fptr_field[7];
    calculate_SOURCE_VOLTAGE_func       = (calculate_SOURCE_VOLTAGE) test_fptr_field[8];
    calculate_FSV_func                  = (calculate_FSV) test_fptr_field[9];
}

struct PAC1720_device dev;


int main(void){
setUp();
char msg[500];

    dev.sensor_config_ch1.source_voltage_sampling_time_reg = 0x02;
    dev.ch1_readings.v_source_voltage_reg = 0b1001100110000000;
    calculate_SOURCE_VOLTAGE_func(&dev.ch1_readings.v_source_voltage_reg, &dev.sensor_config_ch1.source_voltage_sampling_time_reg);
// sprintf(msg, "val: %f\n", res);
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

