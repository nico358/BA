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
int8_t init_device_PAC1720(struct PAC1720_device *device_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
const void** get_TEST_FPTR_FIELD(void);

#ifdef __cplusplus
}
#endif /* End of CPP guard */
/** @}*/