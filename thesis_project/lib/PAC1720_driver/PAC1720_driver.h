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
 * @fn return_device_ptr_BME680
 * @brief Returns the pointer to the instance of the BME680 device structure.
 *
 * @see bme680_dev
 *
 * @return bme680_dev
 */
int8_t init_device_PAC1720(struct PAC1720_device *dev);

/*!
 * @fn return_device_ptr_BME680
 * @brief Returns the pointer to the instance of the BME680 device structure.
 *
 * @see bme680_dev
 *
 * @return bme680_dev
 */
const void* get_TEST_FPTR_FIELD(void);

#ifdef __cplusplus
}
#endif /* End of CPP guard */
/** @}*/