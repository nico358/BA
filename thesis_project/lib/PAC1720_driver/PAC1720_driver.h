/*! @file PAC17Driver.h
 @brief Sensor driver for PAC1720 sensor */
/*!
 * @defgroup PAC1720 driver API
 * @{*/

#pragma once

/*! CPP guard */
#ifdef __cplusplus
extern "C"
{
#endif

/* Header includes */
#include "PAC1720_definitions.h"


/* function prototypes */

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
int8_t init_device_PAC1720(struct PAC1720_device *device_ptr, PAC1720_fptr write, PAC1720_fptr read, delay_fptr delay);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
void destroy_device_PAC1720(struct PAC1720_device *device_ptr);

// int8_t get_measurement_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
uint8_t get_sensor_product_id(struct PAC1720_device *device_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
uint8_t get_sensor_manufact_id(struct PAC1720_device *device_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
uint8_t get_sensor_revision_id(struct PAC1720_device *device_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
float get_channel_FSC(struct PAC1720_CH_config *config_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
float get_channel_FSV(struct PAC1720_CH_config *config_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
float get_channel_FSP(struct PAC1720_CH_config *config_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
uint16_t get_channel_src_voltage_read(struct PAC1720_CH_measurements *meas_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
uint16_t get_channel_sense_voltage_read(struct PAC1720_CH_measurements *meas_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
uint16_t get_channel_pwr_ratio_read(struct PAC1720_CH_measurements *meas_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
const void* get_TEST_DRIVER_FPTR_FIELD(void);

#ifdef __cplusplus
}
#endif /* End of CPP guard */
/** @}*/