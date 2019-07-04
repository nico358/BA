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


/************************************************* Function prototypes ***************************************************/

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
int8_t init_device_PAC1720_from_field(struct PAC1720_device *device_ptr, PAC1720_fptr ext_write, PAC1720_fptr ext_read, delay_fptr ext_delay);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
int8_t init_device_PAC1720_user_defined(struct PAC1720_device *device_ptr, PAC1720_fptr ext_write, PAC1720_fptr ext_read, delay_fptr ext_delay);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
void destroy_device_PAC1720(struct PAC1720_device *device_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
int8_t get_all_measurements_PAC1720(struct PAC1720_device *device_ptr);

/*!
 * @brief
 *
 * 
 * @note ..
 * @param[in] config	: 
 *
 * @return 
 * @retval 1 value -> OK/ 0 value -> Error
 */
int8_t write_out_one_shot_register(struct PAC1720_device *device_ptr);


/***************************************************** Private data getters ****************************************/

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