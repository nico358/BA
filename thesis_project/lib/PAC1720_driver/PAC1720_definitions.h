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

/*! @name PAC1720 device constants*/
/** PAC1720 addresses */
static const uint8_t PAC1720_addresses[16] = {
											  	0x18, 
												0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 
												0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
											 };

/** PAC1720 general configuration register constants */
static const uint8_t 	configuration_register_address 								= 0x00;
/** PAC1720 conversion rate register constants */
static const uint8_t 	conversion_rate_register_address 							= 0x01;
/** PAC1720 one-shot register constants */
static const uint8_t 	one_shot_register_address 									= 0x02;
/** PAC1720 channel mask register constants */
static const uint8_t 	channel_mask_register_address 								= 0x03;
/** PAC1720 limit status register constants */
static const uint8_t 	high_limit_status_register_address 							= 0x04;
static const uint8_t 	low_limit_status_register_address 							= 0x05;
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

typedef enum 			{FIRST_CHANNEL=1, SECOND_CHANNEL=2, BOTH_CHANNELS=3} 		ACTIVE_CHANNELS;
static const uint8_t 	SENSOR_ADDRESS_NUMBER 										= 16;
static const uint8_t 	SENSOR_REGISTERS_NUMBER 									= 32;
static const uint8_t 	READING_REGISTER_OFFSET 									= 9;

static const uint8_t 	BITMASK_MSB_CURRENT_SAMPLE									= 0x70;
static const uint8_t 	BITMASK_FIRST_TWO											= 0xC0;
static const uint8_t 	BITMASK_SECOND_TWO											= 0x30;
static const uint8_t    BITMASK_THIRD_TWO											= 0x0C;
static const uint8_t    BITMASK_FOURTH_TWO 											= 0x03;

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
 * @brief Sensor readings data struct. 
 */
struct	PAC1720_channel_readings 
{
	/*! Reading done flag */
	bool 		reading_done;
	/*! Sensor status byte */
	uint8_t 	status;

	/*! The sensed voltage across sense resistor */
	uint16_t 	v_sense_voltage_reg; 
	/*! The sensed voltage on input pin */
	uint16_t 	v_source_voltage_reg; 
	/*! The sensor determined power ratio */
	uint16_t 	power_ratio_reg; 

	/*! The calculated measurements */
	float 		res_SENSE_VOLTAGE;
	float 		res_SOURCE_VOLTAGE;
	float 		res_CURRENT;
	float 		res_POWER;
};

/*!
 * @brief PAC1720 channel configuration struct
 */
struct	PAC1720_channel_config 
{
	/*! Optional naming of channel */
	char 		*name;

	/*! Sense resistor value, set by device init */
	float 		current_sense_resistor_value;

	/*! Current sensing sampling time settings, 
	*   contained in 'chX_current_sense_sampling_config_reg' */
	uint8_t 	current_sense_sampling_time_reg;
	/*! Current-sensing averaging settings, 
	*   contained in 'chX_current_sense_sampling_config_reg' */
	uint8_t 	current_sense_sampling_average_reg;
	/*! Full Scale Range (FSR): current sensing range,  
	*   contained in 'chX_current_sense_sampling_config_reg' */
	uint8_t 	current_sense_FSR_reg;
	/*! Full Scale Current (FSC), calculated */
	float 		current_sense_FSC;

	/*! Vsource sampling time settings, 
	*   contained in 'source_voltage_sampling_config_reg' */
	uint8_t 	source_voltage_sampling_time_reg;
	/*! Vsource averaging settings, 
	*   contained in 'source_voltage_sampling_config_reg' */
	uint8_t 	source_voltage_sampling_average_reg;
	/*! Full Scale Voltage (FSV), calculated */
	float 		source_voltage_FSV;

	/*! Full Scale Power (FSP), calculated */
	float 		power_sense_FSP;

	/* Sense voltage limit register */
	uint16_t 	current_sense_limit_reg;
	/* Source voltage limit register */
	uint16_t 	source_voltage_limit_reg;
};

/*!
 * @brief PAC1720 device struct.
 */
struct	PAC1720_device 
{	
	/*! Optional naming of device */
	char 	*name;
	/*! Sensor slave address */
	uint8_t sensor_address;
	/*! Sensor channels in use */
	ACTIVE_CHANNELS channels;
	/* Configuration register */
	uint8_t configuration_reg;
	/*! Updating measurements interval */
	uint8_t conversion_rate_reg;
	/* One shot register */
	uint8_t one_shot_reg;
	/* Channel mask register */
	uint8_t channel_mask_reg;
	/* High limit status register */
	uint8_t high_limit_status_reg;
	/* Low limit status register */
	uint8_t low_limit_status_reg;

	/*! Vsource sampling config settings, 
	*   contains different registers for ch1 & ch2 */
	uint8_t source_voltage_sampling_config_reg;
	/*! Vsense sampling config settings, 
	*	contains different registers for ch1 */
	uint8_t ch1_current_sense_sampling_config_reg;
	/*! Vsense sampling config settings, 
	*	contains different registers for ch2 */
	uint8_t ch2_current_sense_sampling_config_reg;

	/* Sensor product id */
	uint8_t sensor_product_id;
	/* Sensor manufacturer id */
	uint8_t sensor_manufact_id;
	/* Sensor revision */
	uint8_t sensor_revision;

	/*! The struct holding the config of channel 1*/
	struct PAC1720_channel_config 	sensor_config_ch1;
	/*! The struct holding the config of channel 2*/
	struct PAC1720_channel_config 	sensor_config_ch2;
	/*! The struct holding the latest readings of channel 1*/
	struct PAC1720_channel_readings ch1_readings;
	/*! The struct holding the latest readings of channel 2*/
	struct PAC1720_channel_readings ch2_readings;

	/*! Bus read function pointer */
	PAC1720_fptr read;
	/*! Bus write function pointer */
	PAC1720_fptr write;
	/*! delay function pointer */
	delay_fptr 	 delay_ms;
};

/** @}*/
/** @}*/