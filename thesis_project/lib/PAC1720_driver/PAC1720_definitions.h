/*! @file PAC1720_definitions.h
    @brief Definitions for PAC1720 sensors */
/*!
 * @defgroup PAC1720 driver API
 * @brief
 * @{*/

#pragma once

/** Header includes */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*! @name PAC1720 device constants*/
/** PAC1720 addresses */
static const uint8_t PAC1720_addresses[16] = {
											  	0x18, 
												0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 
												0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
											 };

/** PAC1720 general configuration register constants */
static const uint8_t configuration_register_address = 0x00;
static const uint8_t conf_reg_bit_C1VDS = 0x00; 
static const uint8_t conf_reg_bit_C1IDS = 0x01; 
static const uint8_t conf_reg_bit_TOUT  = 0x02; 
static const uint8_t conf_reg_bit_C2VDS = 0x03;
static const uint8_t conf_reg_bit_C2IDS = 0x04;
static const uint8_t conf_reg_bit_MSKAL = 0x05;
static const uint8_t conf_reg_bit_CDEN  = 0x06;
/** PAC1720 conversion rate register constants */
static const uint8_t conversion_rate_register_address = 0x01;
static const uint8_t conv_rate_reg_bit_CONV0 = 0x00; 
static const uint8_t conv_rate_reg_bit_CONV1 = 0x01;
/** PAC1720 one-shot register constants */
static const uint8_t one_shot_register_address = 0x02;
static const uint8_t one_shot_reg_bit_OS0 = 0x00; 
static const uint8_t one_shot_reg_bit_OS1 = 0x01;
static const uint8_t one_shot_reg_bit_OS2 = 0x02;
static const uint8_t one_shot_reg_bit_OS3 = 0x03;
static const uint8_t one_shot_reg_bit_OS4 = 0x04;
static const uint8_t one_shot_reg_bit_OS5 = 0x05;
static const uint8_t one_shot_reg_bit_OS6 = 0x06;
static const uint8_t one_shot_reg_bit_OS7 = 0x07;
/** PAC1720 channel mask register constants */
static const uint8_t channel_mask_register_address = 0x03;
static const uint8_t channel_mask_reg_bit_C1VSR  = 0x00; 
static const uint8_t channel_mask_reg_bit_C1VS   = 0x01;
static const uint8_t channel_mask_reg_bit_C2VSR  = 0x02;
static const uint8_t channel_mask_reg_bit_C2VS   = 0x03;
/** PAC1720 limit status register constants */
static const uint8_t high_limit_status_register_address = 0x04;
static const uint8_t high_limit_status_reg_bit_C1VRH    = 0x00; 
static const uint8_t high_limit_status_reg_bit_C1VSH    = 0x01;
static const uint8_t high_limit_status_reg_bit_C2VRH    = 0x02;
static const uint8_t high_limit_status_reg_bit_C2VSH    = 0x03;
static const uint8_t high_limit_status_reg_bit_CVDN     = 0x07;
static const uint8_t low_limit_status_register_address  = 0x05;
static const uint8_t low_limit_status_reg_bit_C1VRL     = 0x00; 
static const uint8_t low_limit_status_reg_bit_C1VSL     = 0x01;
static const uint8_t low_limit_status_reg_bit_C2VRL     = 0x02;
static const uint8_t low_limit_status_reg_bit_C2VSL     = 0x03;
/** PAC1720 sampling configuration register constants */
static const uint8_t v_source_sampling_configuration_register_address = 0x0A;
static const uint8_t v_source_sampling_config_reg_bit_C1RA0 = 0x00; 
static const uint8_t v_source_sampling_config_reg_bit_C1RA1 = 0x01;
static const uint8_t v_source_sampling_config_reg_bit_C1RS0 = 0x02;
static const uint8_t v_source_sampling_config_reg_bit_C1RS1 = 0x03;
static const uint8_t v_source_sampling_config_reg_bit_C2RA0 = 0x04; 
static const uint8_t v_source_sampling_config_reg_bit_C2RA1 = 0x05;
static const uint8_t v_source_sampling_config_reg_bit_C2RS0 = 0x06;
static const uint8_t v_source_sampling_config_reg_bit_C2RS1 = 0x07;
static const uint8_t ch1_v_sense_sampling_configuration_register_address = 0x0B;
static const uint8_t ch1_v_sense_sampling_config_reg_bit_C1SR0 = 0x00; 
static const uint8_t ch1_v_sense_sampling_config_reg_bit_C1SR1 = 0x01;
static const uint8_t ch1_v_sense_sampling_config_reg_bit_C1SA0 = 0x02;
static const uint8_t ch1_v_sense_sampling_config_reg_bit_C1SA1 = 0x03;
static const uint8_t ch1_v_sense_sampling_config_reg_bit_C1SS0 = 0x04; 
static const uint8_t ch1_v_sense_sampling_config_reg_bit_C1SS1 = 0x05;
static const uint8_t ch1_v_sense_sampling_config_reg_bit_C1SS2 = 0x06;
static const uint8_t ch2_v_sense_sampling_configuration_register_address = 0x0C;
static const uint8_t ch2_v_sense_sampling_config_reg_bit_C2SR0 = 0x00; 
static const uint8_t ch2_v_sense_sampling_config_reg_bit_C2SR1 = 0x01;
static const uint8_t ch2_v_sense_sampling_config_reg_bit_C2SA0 = 0x02;
static const uint8_t ch2_v_sense_sampling_config_reg_bit_C2SA1 = 0x03;
static const uint8_t ch2_v_sense_sampling_config_reg_bit_C2SS0 = 0x04; 
static const uint8_t ch2_v_sense_sampling_config_reg_bit_C2SS1 = 0x05;
static const uint8_t ch2_v_sense_sampling_config_reg_bit_C2SS2 = 0x06;
/** PAC1720 readings register constants */
static const uint8_t ch1_sense_voltage_high_register_address    = 0x0D;

static const uint8_t ch1_sense_voltage_low_register_address     = 0x0E;

static const uint8_t ch2_sense_voltage_high_register_address    = 0x0F;

static const uint8_t ch2_sense_voltage_low_register_address     = 0x10;

static const uint8_t ch1_v_source_voltage_high_register_address = 0x11;

static const uint8_t ch1_v_source_voltage_low_register_address  = 0x12;

static const uint8_t ch2_v_source_voltage_high_register_address = 0x13;

static const uint8_t ch2_v_source_voltage_low_register_address  = 0x14;

static const uint8_t ch1_power_ratio_high_register_address      = 0x15;

static const uint8_t ch1_power_ratio_low_register_address       = 0x16;

static const uint8_t ch2_power_ratio_high_register_address      = 0x17;

static const uint8_t ch2_power_ratio_low_register_address       = 0x18;
/** PAC1720 sense high limit register constants */
static const uint8_t ch1_sense_voltage_high_limit_register_address = 0x19;
static const uint8_t ch2_sense_voltage_high_limit_register_address = 0x1A;
/** PAC1720 sense low limit register constants */
static const uint8_t ch1_sense_voltage_low_limit_register_address = 0x1B;
static const uint8_t ch2_sense_voltage_low_limit_register_address = 0x1C;
/** PAC1720 source high limit register constants */
static const uint8_t ch1_v_source_voltage_high_limit_register_address = 0x1D;
static const uint8_t ch2_v_source_voltage_high_limit_register_address = 0x1E;
/** PAC1720 source low limit register constants */
static const uint8_t ch1_v_source_voltage_low_limit_register_address = 0x1F;
static const uint8_t ch2_v_source_voltage_low_limit_register_address = 0x20;
/** PAC1720 device information register constants */
static const uint8_t product_id_register_address                  = 0xFD;
static const uint8_t manufacturer_id_register_address             = 0xFE;
static const uint8_t revision_register_address                    = 0xFF;

/** Configuration specific constants */
/** Possible Full Scale Range values in current sensing, determined by current_sense_FSR_reg */
static const float FSR_values[4] = {0.01f, 0.02f, 0.04f, 0.08f};
/** Possible BUS current formula denominators, determined by current_sense_sampling_time_reg */
static const float DENOMINATOR_values_current_sense[8] = {63.0f, 127.0f, 255.0f, 511.0f, 1023.0f, 2047.0f, 2047.0f, 2047.0f};
static const uint8_t CURRENT_RESOLUTION_IGNORE_BITS[8] = {9,8,7,6,5,4,4,4};
static const uint16_t NEGATIVE_CURRENT_RESOLUTION_MASK[8] = {0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x0FFF, 0x0FFF};
/** Possible FSV formula denominators, determined by source_voltage_sampling_time_reg. Note: Vsource denominators are equal to these -1 */
static const float DENOMINATOR_values_source_voltage[4] = {256.0f, 512.0f, 1024.0f, 2048.0f};
static const uint8_t VSOURCE_RESOLUTION_IGNORE_BITS[4] = {8,7,6,5};
static const float DENOMINATOR_correction_source_voltage = 1.0f;
static const uint8_t SHIFT_TO_SIGN_BIT = 15;

/** Application constants */
static const int8_t PAC1720_OK = 0;
static const int8_t PAC1720_FAILURE = -1;
static const int8_t PAC1720_ADDRESS_ERROR = -2;

typedef enum {FIRST_CHANNEL=1, SECOND_CHANNEL=2, BOTH_CHANNELS=3} ACTIVE_CHANNELS;
static const uint8_t SENSOR_ADDRESS_NUMBER = 16;
static const uint8_t SENSOR_REGISTERS_NUMBER = 32;
static const uint8_t READING_REGISTER_OFFSET = 9;
static const uint8_t SHIFT_IN_BYTES_OFFSET = 8;

/** Type definitions */
/*!
 * Generic communication function pointer
 * @param[in] x: ... .
 * @param[in] y:	... .
 * @param[in/out] z: ... .
 */
typedef int8_t (*PAC1720_fptr)(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);

/*!
 * Delay function pointer
 * @param[in] period: Time period in milliseconds
 */
typedef void (*delay_fptr)(uint32_t period);

/* structure definitions */

/*!
 * @brief Sensor readings data struct. 
 */
struct	PAC1720_channel_readings 
{
	/*! Reading done flag */
	bool reading_done;
	/*! Sensor status byte */
	uint8_t status;
	/*! The sensed voltage across the resistor (Sense+ and Sense-) */
	/*  Signed 11bit number by default, two's complement */
	uint16_t v_sense_voltage_reg; 
	/*! The sensed voltage on input pin (Sense +) */
	/*  Unsigned 11bit number by default */
	uint16_t v_source_voltage_reg; 
	/*! Calculated power ratio (The value represents the percentage of maximum calculable power.) */
	/*  Unsigned 16bit number by default */
	uint16_t power_ratio_reg; 
	/*! The actual values after conversion of the registers */
	float res_SENSE_VOLTAGE;
	float res_SOURCE_VOLTAGE;
	float res_CURRENT;
	float res_POWER;
};

/*!
 * @brief PAC1720 configuration struct
 */
struct	PAC1720_channel_config 
{
	/*! Optional naming of channel */
	char *name;
	/*! Vsource sampling time settings */
	uint8_t source_voltage_sampling_time_reg;  //00=2.5ms (data=8bits) Denom FULL-SCALE VOLTAGE = 256, Denom BUS VOLTAGE = 255, 
									//01=5ms (data=9bits), Denom FULL-SCALE VOLTAGE = 512, Denom BUS VOLTAGE = 511, 
								    //default 10=10ms (data=10bits), Denom FULL-SCALE VOLTAGE = 1024, Denom BUS VOLTAGE = 1023, 
									//11=20ms(data=11bits), Denom FULL-SCALE VOLTAGE = 2048, Denom BUS VOLTAGE = 2047
	/*! Vsource averaging settings */
	uint8_t source_voltage_sampling_average_reg;		//default 00=disabled, 01=2, 10=4, 11=8 
	/*! Full Scale Voltage (FSV)  */
	float source_voltage_FSV;
	/*! Current-sensing averaging settings  */
	uint8_t current_sense_sampling_average_reg;		//default 00=disabled, 01=2, 10=4, 11=8 
	/*! Current sensing sampling time settings (Denominator BUS_CURRENT = (2^resolution) -1) */
	uint8_t current_sense_sampling_time_reg;		//000 2.5 ms sample time (Data = sign + 6 bits) 63 = Denom BUS CURRENT
									//001 5 ms sample time (Data = sign + 7 bits) 127 = Denom BUS CURRENT
									//010 10ms sample time (Data = sign + 8 bits) 255 = Denom BUS CURRENT
									//011 20ms sample time (Data = sign + 9 bits) 511 = Denom BUS CURRENT
									//100 40 ms sample time (Data = sign + 10 bits) 1023 = Denom BUS CURRENT
									//default 101 80 ms sample time (Data = sign + 11 bits) 2047 = Denom BUS CURRENT
									//110 160 ms sample time (Data = sign + 11 bits) 2047 = Denom BUS CURRENT
									//111 320 ms sample time (Data = sign + 11 bits) 2047 = Denom BUS CURRENT
	/*! Full Scale Range (FSR): current sensing range setting */
	/* Default: 0000 0011 = ±80 mV */
	uint8_t current_sense_FSR_reg; 			//(FSR) 00=±10 mV, 01=±20 mV, 10=±40 mV, 11=±80 mV (default)
	/*! Full Scale Current (FSC) */
	float current_sense_FSC;
	/*! Sense resistor value */
	float current_sense_resistor_value;
	/*! Full Scale Power (FSP) */
	float power_sense_FSP;
	/* Sense voltage limit register */
	uint16_t current_sense_limit_reg;
	/* Source voltage limit register */
	uint16_t source_voltage_limit_reg;
};

/*!
 * @brief PAC1720 device struct.
 */
struct	PAC1720_device 
{	
	/*! Optional naming of device */
	char *name;
	/*! Sensor slave address */
	uint8_t sensor_address;
	/*! Sensor channels in use */
	ACTIVE_CHANNELS channels;
	/* Configuration register */
	uint8_t configuration_reg;
	/*! Specify how often measured data are updated in active state
	 *  update only in stdby state (disable measurements in config reg, 
	 *  wait to conversion complete (monitor XMEAS_DIS bit in config reg, stay set to 1)) */
	uint8_t conversion_rate_reg; 				//00=1/s, 01=2/s, 10=4/s, 11=continious(default)
	/* One shot register */
	uint8_t one_shot_reg;
	/* Channel mask register */
	uint8_t channel_mask_reg;
	/* High limit status register */
	uint8_t high_limit_status_reg;
	/* Low limit status register */
	uint8_t low_limit_status_reg;
	/*! Vsource sampling time settings */
	uint8_t source_voltage_sampling_time_reg;  	//00=2.5ms (data=8bits) Denom FULL-SCALE VOLTAGE = 256, Denom BUS VOLTAGE = 255, 
												//01=5ms (data=9bits), Denom FULL-SCALE VOLTAGE = 512, Denom BUS VOLTAGE = 511, 
								    			//default 10=10ms (data=10bits), Denom FULL-SCALE VOLTAGE = 1024, Denom BUS VOLTAGE = 1023, 
												//11=20ms(data=11bits), Denom FULL-SCALE VOLTAGE = 2048, Denom BUS VOLTAGE = 2047
	/*! The struct holding the config of channel 1*/
	struct PAC1720_channel_config sensor_config_ch1;
	/*! The struct holding the config of channel 2*/
	struct PAC1720_channel_config sensor_config_ch2;
	/*! The struct holding the latest readings of channel 1*/
	struct PAC1720_channel_readings ch1_readings;
	/*! The struct holding the latest readings of channel 2*/
	struct PAC1720_channel_readings ch2_readings;
	/*! Bus read function pointer */
	PAC1720_fptr read;
	/*! Bus write function pointer */
	PAC1720_fptr write;
	/*! delay function pointer */
	delay_fptr delay_ms;
	/* Sensor product id */
	uint8_t sensor_product_id;
	/* Sensor manufacturer id */
	uint8_t sensor_manufact_id;
	/* Sensor revision */
	uint8_t sensor_revision;

};

/** @}*/
/** @}*/