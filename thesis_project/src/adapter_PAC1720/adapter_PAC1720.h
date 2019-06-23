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
#include "lib/PAC1720_driver/PAC1720_driver.h"

/*! CPP guard */
#ifdef __cplusplus
extern "C"
{
#endif

/* function prototypes */

/*!
 * @fn return_device_ptr_BME680
 * @brief Returns the pointer to the instance of the BME680 device structure.
 *
 * @see bme680_dev
 *
 * @return bme680_dev
 */
int8_t adapter_init_PAC1720(struct PAC1720_device *dev_ptr, const uint8_t sensor_address, const ACTIVE_CHANNELS channels);

/*!
 * @fn return_device_ptr_BME680
 * @brief Returns the pointer to the instance of the BME680 device structure.
 *
 * @see bme680_dev
 *
 * @return bme680_dev
 */
const void* get_ADAPTER_TEST_FPTR_FIELD(void);

void circular_test(void);


#ifdef __cplusplus
}
#endif /* End of CPP guard */
/** @}*/