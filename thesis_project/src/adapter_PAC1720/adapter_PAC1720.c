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
#include "adapter_PAC1720.h"
#include "lib/i2cmaster/i2cmaster.h"
#include "lib/circular_buffer/circular_buffer.h"
#include "lib/delay/user_delay.h"

/** Function prototypes **/

/*!
 * @fn user_delay_ms
 * @brief This internal API provides the platform dependend delay functionality.
 *
 * @note Required as used in the BME680 API (e.g. sensor read) and passed by pointer to the adapter device.
 *
 * @param period	: 32bit integer. Defined in sensor settings and provided by sensor device struct.
 *
 */
int8_t adapter_i2c_write(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);

/*!
 * @fn user_delay_ms
 * @brief This internal API provides the platform dependend delay functionality.
 *
 * @note Required as used in the BME680 API (e.g. sensor read) and passed by pointer to the adapter device.
 *
 * @param period	: 32bit integer. Defined in sensor settings and provided by sensor device struct.
 *
 */
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
void adapter_delay(uint32_t period);

/*!
 * @fn user_delay_ms
 * @brief This internal API provides the platform dependend delay functionality.
 *
 * @note Required as used in the BME680 API (e.g. sensor read) and passed by pointer to the adapter device.
 *
 * @param period	: 32bit integer. Defined in sensor settings and provided by sensor device struct.
 *
 */
int8_t sensor_address_out_of_range(const uint8_t address);

/*!
 * @fn user_delay_ms
 * @brief This internal API provides the platform dependend delay functionality.
 *
 * @note Required as used in the BME680 API (e.g. sensor read) and passed by pointer to the adapter device.
 *
 * @param period	: 32bit integer. Defined in sensor settings and provided by sensor device struct.
 *
 */
int8_t channels_out_of_range(const ACTIVE_CHANNELS channels);


/** Function definitions **/
int8_t adapter_init_PAC1720(struct PAC1720_device *dev_ptr, const uint8_t sensor_address, const ACTIVE_CHANNELS channels)
{
        if(dev_ptr != NULL && !sensor_address_out_of_range(sensor_address) && !channels_out_of_range(channels)){
            dev_ptr->sensor_address = sensor_address;
            dev_ptr->channels = channels;
            dev_ptr->read = &adapter_i2c_read;
            dev_ptr->write = &adapter_i2c_write;
            dev_ptr->delay_ms = &adapter_delay;

            return init_device_PAC1720(dev_ptr);
        } else {
            return PAC1720_FAILURE;
        }
}

int8_t adapter_i2c_write(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len)
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

void adapter_delay(uint32_t period)
{
    /* External delay function */
    user_delay_ms(period);
}

int8_t sensor_address_out_of_range(const uint8_t address)
{
    if(address == 0x18 || (address > 0x27 && address < 0x2F) || (address > 0x47 && address < 0x50)){
        return PAC1720_OK;
    }
    return PAC1720_ADDRESS_ERROR;
}

int8_t channels_out_of_range(const ACTIVE_CHANNELS channels)
{
    if(channels >= FIRST_CHANNEL && channels <= BOTH_CHANNELS){
        return PAC1720_OK;
    }
    return PAC1720_ADDRESS_ERROR;
}

const void* get_ADAPTER_TEST_FPTR_FIELD(void)
{
    static const void* test_fptr_field[] =  {
                                                 (void*) &adapter_i2c_write,
                                                 (void*) &adapter_i2c_read,
                                                 (void*) &adapter_delay,
                                                 (void*) &sensor_address_out_of_range,
                                                 (void*) &channels_out_of_range
                                            };

    return test_fptr_field;
}

//USB_VCC (Rsense = 0.15Ohm), MON_VCC (Rsense = 0.8Ohm)					= 100Ohm => 1001_101 = 4D
//FPGA_VCCINT_MON (Rsense = 0.8Ohm), FPGA_VCCAUX_MON (Rsense = 0.8Ohm)	= 300Ohm => 1001_111 = 4F
//WIRELESS_VCC (Rsense = 0.8Ohm), MCU_VCC (Rsense = 0.8Ohm)				= 2k  	 => 0101_001 = 29

void circular_test(void){
    circularBuffer buf;
    circBufInit(&buf, 200);
}