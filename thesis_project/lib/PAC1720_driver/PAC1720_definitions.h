/*! @file PAC1720_definitions.h
*    @brief Definitions for PAC1720 sensors 
*/
/*!
 * @defgroup PAC1720 driver API
 * @brief
 * 
 * @{*/

#pragma once

/** Header includes */ 
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

/*! @name PAC1720 device constants*/
/** PAC1720 addresses */
static const uint8_t PAC1720_addresses[16] = {
											  	0x18, 
												0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 
												0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
											 };

/** PAC1720 general configuration register constants */
static const uint8_t 	configuration_register_address 								= 0x00;
static const uint8_t 	conf_reg_bit_C1VDS 											= 0x00; 
static const uint8_t 	conf_reg_bit_C1IDS 											= 0x01; 
static const uint8_t 	conf_reg_bit_TOUT  											= 0x02; 
static const uint8_t 	conf_reg_bit_C2VDS 											= 0x03;
static const uint8_t 	conf_reg_bit_C2IDS 											= 0x04;
static const uint8_t 	conf_reg_bit_MSKAL 											= 0x05;
static const uint8_t 	conf_reg_bit_CDEN  											= 0x06;
/** PAC1720 conversion rate register constants */
static const uint8_t 	conversion_rate_register_address 							= 0x01;
/** PAC1720 one-shot register constants */
static const uint8_t 	one_shot_register_address 									= 0x02;
static const uint8_t 	one_shot_reg_bit_OS0 										= 0x00; 
static const uint8_t 	one_shot_reg_bit_OS1 										= 0x01;
static const uint8_t 	one_shot_reg_bit_OS2 										= 0x02;
static const uint8_t 	one_shot_reg_bit_OS3 										= 0x03;
static const uint8_t 	one_shot_reg_bit_OS4 										= 0x04;
static const uint8_t 	one_shot_reg_bit_OS5 										= 0x05;
static const uint8_t 	one_shot_reg_bit_OS6 										= 0x06;
static const uint8_t 	one_shot_reg_bit_OS7 										= 0x07;
/** PAC1720 channel mask register constants */
static const uint8_t 	channel_mask_register_address 								= 0x03;
static const uint8_t 	channel_mask_reg_bit_C1VSR  								= 0x00; 
static const uint8_t 	channel_mask_reg_bit_C1VS   								= 0x01;
static const uint8_t 	channel_mask_reg_bit_C2VSR  								= 0x02;
static const uint8_t 	channel_mask_reg_bit_C2VS   								= 0x03;
/** PAC1720 high limit status register constants */
static const uint8_t 	high_limit_status_register_address 							= 0x04;
static const uint8_t 	high_limit_status_reg_bit_C1VRH    							= 0x00; 
static const uint8_t 	high_limit_status_reg_bit_C1VSH    							= 0x01;
static const uint8_t 	high_limit_status_reg_bit_C2VRH    							= 0x02;
static const uint8_t 	high_limit_status_reg_bit_C2VSH    							= 0x03;
static const uint8_t 	high_limit_status_reg_bit_CVDN     							= 0x07;
/** PAC1720 low limit status register constants */
static const uint8_t 	low_limit_status_register_address 							= 0x05;
static const uint8_t 	low_limit_status_reg_bit_C1VRL     							= 0x00; 
static const uint8_t 	low_limit_status_reg_bit_C1VSL     							= 0x01;
static const uint8_t 	low_limit_status_reg_bit_C2VRL     							= 0x02;
static const uint8_t 	low_limit_status_reg_bit_C2VSL     							= 0x03;
/** PAC1720 sampling configuration register constants */
static const uint8_t 	v_source_sampling_configuration_register_address 			= 0x0A;
static const uint8_t 	ch1_v_sense_sampling_configuration_register_address 		= 0x0B;
static const uint8_t 	ch2_v_sense_sampling_configuration_register_address 		= 0x0C;
/** PAC1720 readings register constants */
static const uint8_t 	ch1_sense_voltage_high_register_address    					= 0x0D;
static const uint8_t 	ch1_sense_voltage_low_register_address     					= 0x0E;
static const uint8_t 	ch2_sense_voltage_high_register_address    					= 0x0F;
static const uint8_t 	ch2_sense_voltage_low_register_address     					= 0x10;
static const uint8_t 	ch1_v_source_voltage_high_register_address 					= 0x11;
static const uint8_t 	ch1_v_source_voltage_low_register_address  					= 0x12;
static const uint8_t 	ch2_v_source_voltage_high_register_address 					= 0x13;
static const uint8_t 	ch2_v_source_voltage_low_register_address					= 0x14;
static const uint8_t 	ch1_power_ratio_high_register_address      					= 0x15;
static const uint8_t 	ch1_power_ratio_low_register_address       					= 0x16;
static const uint8_t 	ch2_power_ratio_high_register_address      					= 0x17;
static const uint8_t 	ch2_power_ratio_low_register_address       					= 0x18;
/** PAC1720 sense high limit register constants */
static const uint8_t 	ch1_sense_voltage_high_limit_register_address 				= 0x19;
static const uint8_t 	ch2_sense_voltage_high_limit_register_address 				= 0x1A;
/** PAC1720 sense low limit register constants */
static const uint8_t 	ch1_sense_voltage_low_limit_register_address 				= 0x1B;
static const uint8_t 	ch2_sense_voltage_low_limit_register_address 				= 0x1C;
/** PAC1720 source high limit register constants */
static const uint8_t 	ch1_v_source_voltage_high_limit_register_address 			= 0x1D;
static const uint8_t 	ch2_v_source_voltage_high_limit_register_address 			= 0x1E;
/** PAC1720 source low limit register constants */
static const uint8_t 	ch1_v_source_voltage_low_limit_register_address 			= 0x1F;
static const uint8_t 	ch2_v_source_voltage_low_limit_register_address 			= 0x20;
/** PAC1720 device information register constants */
static const uint8_t 	product_id_register_address                  				= 0xFD;
static const uint8_t 	manufacturer_id_register_address             				= 0xFE;
static const uint8_t 	revision_register_address                    				= 0xFF;

/* Configuration setting constants */
enum CONVERSION_RATE 				{CONVERSION_1HZ, CONVERSION_2HZ, CONVERSION_4HZ, CONVERSION_CONTINIOUS};

enum SOURCE_VOLTAGE_SAMPLING_TIME 	{VSRC_SAMPLE_TIME_2ms5, VSRC_SAMPLE_TIME_5ms, VSRC_SAMPLE_TIME_10ms, VSRC_SAMPLE_TIME_20ms};

enum SAMPLE_AVERAGING 				{SAMPLE_AVERAGING_DISABLED, SAMPLE_AVERAGES_2, SAMPLE_AVERAGES_4, SAMPLE_AVERAGES_8};

enum CURRENT_SENSE_SAMPLING_TIME 	{CURRENT_SAMPLE_TIME_2ms5, CURRENT_SAMPLE_TIME_5ms, CURRENT_SAMPLE_TIME_10ms, CURRENT_SAMPLE_TIME_20ms, 
									 CURRENT_SAMPLE_TIME_40ms, CURRENT_SAMPLE_TIME_80ms, CURRENT_SAMPLE_TIME_160ms, CURRENT_SAMPLE_TIME_320ms};

enum CURRENT_SENSE_RANGE 			{CURRENT_SENSE_RANGE_10mV, CURRENT_SENSE_RANGE_20mV, CURRENT_SENSE_RANGE_40mV, CURRENT_SENSE_RANGE_80mV};

/** Calculation specific constants */
/** Possible Full Scale Range values in current sensing, 
 *  determined by 'current_sense_FSR_reg' */
static const float 		FSR_values[4] 												= {0.01f, 0.02f, 0.04f, 0.08f};
/** Possible BUS current formula denominators, 
 *  determined by 'current_sense_sampling_time_reg' */
static const float 		DENOMINATOR_values_current_sense[8] 						= {63.0f, 127.0f, 255.0f, 511.0f, 1023.0f, 2047.0f, 2047.0f, 2047.0f};
/** Ignore register bits (sense resolution) in BUS current formula, 
 *  determined by 'current_sense_sampling_time_reg' */
static const uint8_t 	CURRENT_RESOLUTION_IGNORE_BITS[8] 							= {9,8,7,6,5,4,4,4};
/** Ignore upper bits in two's complement calculation of Vsense, 
 *  determined by 'current_sense_sampling_time_reg' */
static const uint16_t 	NEGATIVE_CURRENT_RESOLUTION_MASK[8] 						= {0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x0FFF, 0x0FFF};
/** Sign bit in int8_t, used to check polarity of Vsense reg */
static const uint8_t 	SHIFT_TO_SIGN_BIT 											= 15;

/** Possible FSV formula denominators, 
 *  determined by 'source_voltage_sampling_time_reg' */
/** Note: Vsource formula denominators are equal to these 
 * 	minus 'DENOMINATOR_correction_source_voltage' */
static const float 		DENOMINATOR_values_source_voltage[4] 						= {256.0f, 512.0f, 1024.0f, 2048.0f};
/** Ignore register bits (sense resolution) in BUS voltage formula, 
 *  determined by 'source_voltage_sampling_time_reg' */
static const uint8_t 	VSOURCE_RESOLUTION_IGNORE_BITS[4] 							= {8,7,6,5};
/** The DENOMINATOR correction value for Vsource calculation */
static const float 		DENOMINATOR_correction_source_voltage 						= 1.0f;


/** Application constants */
static const int8_t 	PAC1720_OK 													= 0;
static const int8_t 	PAC1720_FAILURE 											= -1;
static const int8_t 	PAC1720_ADDRESS_ERROR 										= -2;
static const int8_t 	PAC1720_NULLPTR_ERROR										= -3;
static const int8_t 	PAC1720_INIT_ERROR											= -4;
static const int8_t 	PAC1720_UNSIGNED_ERROR										= 0xFF;

typedef enum 			{FIRST_CHANNEL=1, SECOND_CHANNEL=2, BOTH_CHANNELS=3} 		ACTIVE_CHANNELS;
static const uint8_t 	SENSOR_ADDRESS_NUMBER 										= 16;
static const uint8_t 	SENSOR_REGISTERS_NUMBER 									= 32;

static const uint8_t	GLOBAL_CONFIG_REGISTERS_LENGTH								= 6;
static const uint8_t	VSOURCE_SAMPLING_REGISTER_OFFSET							= 6;
static const uint8_t	CH1_VSENSE_SAMPLING_REGISTER_OFFSET							= 7;
static const uint8_t	CH2_VSENSE_SAMPLING_REGISTER_OFFSET							= 8;
static const uint8_t 	READING_REGISTERS_OFFSET 									= 9;
static const uint8_t 	READING_REGISTERS_LENGTH 									= 12;
static const uint8_t	LIMIT_REGISTERS_OFFSET										= 21;
static const uint8_t	LIMIT_REGISTERS_LENGTH										= 8;
static const uint8_t	CONFIG_READINGS_LIMITS_REGISTERS_LENGTH						= 23;
static const uint8_t	SENSOR_INFO_REGISTER_OFFSET									= 29;
static const uint8_t	SENSOR_INFO_REGISTER_LENGHT									= 3;

static const uint8_t 	BITMASK_MSB_CURRENT_SAMPLE									= 0x70;
static const uint8_t 	BITMASK_FIRST_TWO											= 0xC0;
static const uint8_t 	BITMASK_SECOND_TWO											= 0x30;
static const uint8_t    BITMASK_THIRD_TWO											= 0x0C;
static const uint8_t    BITMASK_FOURTH_TWO 											= 0x03;
static const uint8_t 	BITMASK_CONVERSION_CMPL										= 0x80;

static const uint8_t 	SHIFT_IN_BYTES_OFFSET 										= 8;
static const uint8_t 	SHIFT_SIX_BITS												= 6;
static const uint8_t 	SHIFT_FOUR_BITS												= 4;
static const uint8_t 	SHIFT_TWO_BITS												= 2;

/** Type definitions */
/*!
 * Generic communication function pointer
 * @param[in] x: ... .
 * @param[in] y:	... .
 * @param[in/out] z: ... .
 */
typedef int8_t (*PAC1720_fptr) (const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);

/*!
 * Delay function pointer
 * @param[in] period: Time period in milliseconds
 */
typedef void (*delay_fptr) (uint32_t period);


/* Structure definitions */
/*!
 * @brief  
 */
/* Internal config values */
struct 	PAC1720_internal;
struct  PAC1720_ch_internal;
struct 	PAC1720_meas_internal;

/*! The channels status flags and calculated measurements */
struct 	PAC1720_CH_measurements 
{
	bool 						conversion_done;
	bool 						source_voltage_high_limit;
	bool 						source_voltage_low_limit;
	bool 						sense_voltage_high_limit;
	bool 						sense_voltage_low_limit;

	float 						SOURCE_VOLTAGE;
	float 						SENSE_VOLTAGE;
	float 						CURRENT;
	float 						POWER;

	struct PAC1720_meas_internal * meas_internal;
};

/* Channel specific configuration */
struct 	PAC1720_CH_config
{
	/*! Optional name  */
	char *						 CH_name_opt;
	/*! Sense resistor value */
	float 						 CH_current_sense_resistor_value;
	/*! Current sensing sampling time settings  */
	uint8_t 					 CH_current_sense_sampling_time_reg;
	/*! Current sensing averaging settings */
	uint8_t 					 CH_current_sense_sampling_average_reg;
	/*! Full Scale Range (FSR): current sensing range */
	uint8_t 					 CH_current_sense_FSR_reg;
	/* Sense voltage limit register */
	uint16_t 					 CH_current_sense_limit_reg;
	/*! Source voltage sampling time settings */
	uint8_t 					 CH_source_voltage_sampling_time_reg;
	/*! Source voltage averaging settings */
	uint8_t 					 CH_source_voltage_sampling_average_reg;
	/* Source voltage limit register */
	uint16_t 					 CH_source_voltage_limit_reg;
	/* Mask register */
	uint8_t 					 CH_mask_reg;

	struct PAC1720_ch_internal * ch_internal;
};

/*! The struct holding the device setup and measurements */
struct 	PAC1720_device
{
	/*! Optional name for device */
	char *							DEV_name_opt;
	/*! Sensor slave address */
	uint8_t 						DEV_sensor_address;
	/*! Sensor channels in use */
	ACTIVE_CHANNELS 				DEV_channels;
	/* Configuration register */
	uint8_t 						DEV_configuration_reg;
	/*! Updating measurements interval */
	uint8_t 						DEV_conversion_rate_reg;
	/* One shot register */
	uint8_t 						DEV_one_shot_reg;

	/*! Channel 1 configuration */
	struct PAC1720_CH_config 		DEV_CH1_conf;
	/*! Channel 2 configuration */
	struct PAC1720_CH_config 		DEV_CH2_conf;

	/*! Channel 1 measurements */
	struct PAC1720_CH_measurements 	DEV_CH1_measurements;
	/*! Channel 2 measurements */
	struct PAC1720_CH_measurements	DEV_CH2_measurements;

	struct PAC1720_internal *		internal;
};

/** @}*/
/** @}*/
