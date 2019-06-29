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

/** Defines the data direction (reading from I2C device) in i2c_start(),i2c_rep_start() */
#ifndef I2C_READ
#define I2C_READ    1
#endif
/** Defines the data direction (writing to I2C device) in i2c_start(),i2c_rep_start() */
#ifndef I2C_WRITE
#define I2C_WRITE   0
#endif
/** Defines the number of bits in address shift */
#define I2C_ADDRESS_SHIFT  1

static const uint8_t max_search_attempts = 10;

/** Field- Bus communication struct interface define */
struct BUS_INTERFACE_I2C
{
    void (*init)(void);
    void (*stop)(void);
    unsigned char (*start)(unsigned char address);
    unsigned char (*repStart)(unsigned char address);
    void (*startWait)(unsigned char address);
    unsigned char (*write)(unsigned char data);
    unsigned char (*readAck)(void);
    unsigned char (*readNak)(void);
};

/** Delay functionpointer define */
typedef void (*user_delay_fptr) (uint32_t period);


/* Function prototypes */
/*!
 * @fn 
 * @brief 
 *
 *
 * @return 
 */
int8_t adapter_init_PAC1720(
                            struct PAC1720_device *dev_ptr, 
                            char *dev_name, 
                            char *CH1_name, 
                            char *CH2_name, 
                            const struct BUS_INTERFACE_I2C *extI2C, 
                            const user_delay_fptr delay_fptr, 
                            const uint8_t sensor_address, 
                            const float CH1_sense_resistance,
                            const float CH2_sense_resistance,
                            const ACTIVE_CHANNELS channels
                           );

int8_t get_measurements( struct PAC1720_device *dev_ptr );

/* function prototypes */
/*!
 * @fn
 * @brief
 *
 * @return 
 */
uint8_t adapter_find_sensors(const struct BUS_INTERFACE_I2C *i2c_ptr, const user_delay_fptr delay_ptr, uint8_t *addresses);

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