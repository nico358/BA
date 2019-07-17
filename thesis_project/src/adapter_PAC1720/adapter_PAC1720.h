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

/********************************************* Defines ************************************/
/** Defines the data direction (reading from I2C device) in i2c_start(),i2c_rep_start() */
#ifndef I2C_READ
#define I2C_READ    1
#endif
/** Defines the data direction (writing to I2C device) in i2c_start(),i2c_rep_start() */
#ifndef I2C_WRITE
#define I2C_WRITE   0
#endif

/** Defines the number of bits in address shift */
static const uint8_t BUS_ADDRESS_SHIFT   = 1;

/** Define max attempts to search for active sensors */
static const uint8_t max_search_attempts = 10;


/******************************** Platform dependendet implementation **********************/
/** Field- Bus communication struct interface define */
struct FIELD_BUS_INTERFACE
{
    void            (*init)     (void);
    void            (*stop)     (void);
    unsigned char   (*start)    (unsigned char address);
    unsigned char   (*repStart) (unsigned char address);
    void            (*startWait)(unsigned char address);
    unsigned char   (*write)    (unsigned char data);
    unsigned char   (*readAck)  (void);
    unsigned char   (*readNak)  (void);
};

/** Delay functionpointer define */
typedef void (*delay_function_ptr)  (uint32_t period);
/** Debug functionpointer define */
typedef void (*debugWriteLine_fptr) (char *s);


/******************************** Instances ***********************************************/
/** Sensor struct instances */
extern struct PAC1720_device        dev_USB_MON;
extern struct PAC1720_device        dev_FPGA_VCC;
extern struct PAC1720_device        dev_WIREL_MCU;


/******************************** Function prototypes *************************************/

/*!
 * @fn 
 * @brief 
 *
 *
 * @return 
 */
void adapter_init_peripherals(struct FIELD_BUS_INTERFACE *fieldbus_interface, delay_function_ptr delay_fptr);

/*!
 * @fn 
 * @brief 
 *
 *
 * @return 
 */
int8_t adapter_init_PAC1720_from_field(struct PAC1720_device *dev_ptr);

/*!
 * @fn 
 * @brief 
 *
 *
 * @return 
 */
int8_t adapter_init_PAC1720_user_defined(struct PAC1720_device *dev_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
void adapter_destroy_PAC1720(struct PAC1720_device *device_ptr);

/*!
 * @fn 
 * @brief 
 *
 * @see
 *
 * @return 
 */
int8_t adapter_get_measurements_PAC1720(struct PAC1720_device *device_ptr);

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
int8_t adapter_write_one_shot_PAC1720(struct PAC1720_device *device_ptr);

/*!
 * @fn
 * @brief
 *
 * @return 
 */
uint8_t adapter_find_sensors(uint8_t *addresses, struct FIELD_BUS_INTERFACE *fieldbus_interface, delay_function_ptr delay_fptr);

/*!
 * @fn 
 * @brief 
 *
 *
 * @return 
 */
void debug_PAC1720(struct PAC1720_device * dev, debugWriteLine_fptr debug_fptr);

/*!
 * @fn 
 * @brief 
 *
 *
 * @return 
 */
void print_measurements_PAC1720(struct PAC1720_device * dev, debugWriteLine_fptr debug_fptr);

/*!
 * @fn 
 * @brief 
 *
 *
 * @return 
 */
const void* get_ADAPTER_TEST_FPTR_FIELD(void);

#ifdef __cplusplus
}
#endif /* End of CPP guard */
/** @}*/
