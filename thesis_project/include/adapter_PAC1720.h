/*
 * adapter_PAC1720.h
 *
 */

/**
* @file	adapter_PAC1720.h
* @brief
*/

#pragma once

/** Includes **/
#include <stdint.h>

/*! CPP guard */
#ifdef __cplusplus
extern "C"
{
#endif

/*!
 *
 * @{*/

/** macros */

/** @}*/

/* function prototype declarations */
/*!
 * @fn return_device_ptr_BME680
 * @brief Returns the pointer to the instance of the BME680 device structure.
 *
 * @see bme680_dev
 *
 * @return bme680_dev
 */
int8_t adapter_i2c_write(const uint8_t sensor_address, const uint8_t reg_address, const uint8_t *data_ptr, const uint16_t len);


#ifdef __cplusplus
}
#endif /* End of CPP guard */
