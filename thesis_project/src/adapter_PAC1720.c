/**
 * File		adapter_BME680.c
 * @date	20 Mai 2018
 * @version	1.0
 *
 */

/*! @file adapter_bme680.c
 *  @brief Adapter for BME680 sensor API
 */

/** Header includes **/
#include "include/adapter_PAC1720.h"
#include "lib/PAC1720_driver/PAC1720_driver.h"
#include "lib/i2cmaster/i2cmaster.h"
#include "lib/circular_buffer/circular_buffer.h"
#include "lib/delay/user_delay.h"

/** Function prototypes **/
int8_t adapter_init_PAC1720(struct PAC1720_device *dev_ptr, const uint8_t sensor_address, const ACTIVE_CHANNELS channels);

// int8_t adapter_i2c_write(const uint8_t sensor_address, const uint8_t reg_address, const uint8_t *data_ptr, const uint16_t len);

int8_t adapter_i2c_read(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);

/*!
 * @fn user_delay_ms
 * @brief This internal API provides the platform dependend delay functionality.
 *
 * @note Required as used in the BME680 API (e.g. sensor read) and passed by pointer to the adapter device.
 *
 * @param period	: 32bit integer. Defined in sensor settings and provided by sensor device struct.
 *
 */
void adapter_delay(const uint32_t period);

/** Function definitions **/
int8_t adapter_init_PAC1720(struct PAC1720_device *dev_ptr, const uint8_t sensor_address, const ACTIVE_CHANNELS channels)
{
        if(dev_ptr != NULL){
            dev_ptr->sensor_address = sensor_address;
            dev_ptr->channels = channels;
            dev_ptr->read = &adapter_i2c_read;
            dev_ptr->write = &adapter_i2c_write;
            dev_ptr->delay_ms = &adapter_delay;
            return PAC1720_OK;
        } else {
            return PAC1720_FAILURE;
        }
        

}

int8_t adapter_i2c_write(const uint8_t sensor_address, const uint8_t reg_address, const uint8_t *data_ptr, const uint16_t len)
{
    uint8_t result = PAC1720_OK;
    i2c_start_wait((sensor_address << I2C_ADDRESS_SHIFT) + I2C_WRITE); 
    result = i2c_write(reg_address);
    if(result != PAC1720_OK) return result;
    /* Write to #len registers, increase the address #len times */
    for(uint16_t i = 0; i < len; i++){
        result = i2c_write(*data_ptr);
            if(result != PAC1720_OK) return result;
            data_ptr++;
    }
    i2c_stop();
    return result;
}

int8_t adapter_i2c_read(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len)
{
    uint8_t result = PAC1720_OK;
    i2c_start_wait((sensor_address << I2C_ADDRESS_SHIFT) + I2C_WRITE);
    result = i2c_write(reg_address);
    /* Repeat start in read mode */
    result = i2c_rep_start((sensor_address << I2C_ADDRESS_SHIFT) + I2C_READ);
    /* Read from #len registers, increase the address #len times */
    for(uint16_t i = 0; i < len; i++){
        if(i < len -1){
            *data_ptr = i2c_readAck();
        }else{
            /* After the last read send NACK */
            *data_ptr = i2c_readNak(); 
        }
        data_ptr++;
    }
    i2c_stop();
    return result;
}

void adapter_delay(const uint32_t period)
{
    /* External delay function */
    user_delay_ms(period);
}



