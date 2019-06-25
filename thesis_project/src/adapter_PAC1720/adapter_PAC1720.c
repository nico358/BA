/**
 * File		
 *
 */

/*! @file 
 *  @brief
 */

/** Header includes **/
#include "adapter_PAC1720.h"


/** Function prototypes **/

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
int8_t adapter_i2c_write(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
int8_t adapter_i2c_read(const uint8_t sensor_address, const uint8_t reg_address, uint8_t *data_ptr, const uint16_t len);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
void adapter_delay(uint32_t period);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
uint8_t poll_i2c(const struct BUS_INTERFACE_I2C *i2c_ptr, uint8_t loop_var, uint8_t *addresses);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
bool sensor_address_out_of_range(const uint8_t address);

/*!
 * @fn 
 * @brief
 *
 * @note 
 *
 * @param .
 *
 */
bool channels_out_of_range(const ACTIVE_CHANNELS channels);


/** Internal I2C Field-Bus interface  */
const struct BUS_INTERFACE_I2C *i2c = NULL;
/** Internal delay fptr */
user_delay_fptr user_delay = NULL;


/** Function definitions */

int8_t adapter_init_PAC1720( 
                             struct PAC1720_device *dev_ptr, 
                             char *dev_name, 
                             char *CH1_name, 
                             char *CH2_name,
                             const struct BUS_INTERFACE_I2C *ext_I2C, 
                             const user_delay_fptr ext_delay_fptr, 
                             const uint8_t sensor_address, 
                             const ACTIVE_CHANNELS channels 
                           )
{
        if ( dev_ptr != NULL && ext_I2C != NULL && ext_delay_fptr != NULL 
             && !sensor_address_out_of_range(sensor_address) 
             && !channels_out_of_range(channels) 
           )
        {
            i2c = ext_I2C;
            user_delay = ext_delay_fptr;
            dev_ptr->sensor_address = sensor_address;
            dev_ptr->channels = channels;
            dev_ptr->read = &adapter_i2c_read;
            dev_ptr->write = &adapter_i2c_write;
            dev_ptr->delay_ms = &adapter_delay;
            dev_ptr->name = dev_name;
            dev_ptr->sensor_config_ch1.name = CH1_name;
            dev_ptr->sensor_config_ch2.name = CH2_name;

            return init_device_PAC1720(dev_ptr);
        } else {
            return PAC1720_FAILURE;
        }
}

int8_t adapter_i2c_write( 
                          const uint8_t sensor_address, 
                          const uint8_t reg_address, 
                          uint8_t *data_ptr, 
                          const uint16_t len 
                        )
{
    uint8_t result = PAC1720_OK;
    i2c->startWait((sensor_address << I2C_ADDRESS_SHIFT) + I2C_WRITE); 
    result = i2c->write(reg_address);

    if(result != PAC1720_OK) return result;

    /* Write to #len registers, increase the address #len times */
    for(uint16_t i = 0; i < len; i++){
        result = i2c->write(*data_ptr);
            if(result != PAC1720_OK) return result;
            data_ptr++;
    }

    i2c->stop();
    return result;
}

int8_t adapter_i2c_read ( 
                          const uint8_t sensor_address, 
                          const uint8_t reg_address, 
                          uint8_t *data_ptr, 
                          const uint16_t len 
                        )
{
    uint8_t result = PAC1720_OK;
    i2c->startWait((sensor_address << I2C_ADDRESS_SHIFT) + I2C_WRITE);
    result = i2c->write(reg_address); 

    /* Repeat start in read mode */
    result = i2c->repStart((sensor_address << I2C_ADDRESS_SHIFT) + I2C_READ);

    /* Read from #len registers, increase the address #len times */
    for(uint16_t i = 0; i < len; i++){
        if(i < len -1){
            *data_ptr = i2c->readAck();
        }else{
            /* After the last read send NACK */
            *data_ptr = i2c->readNak(); 
        }
        data_ptr++;
    }

    i2c->stop();
    return result;
}

void adapter_delay(uint32_t period)
{
    /* External delay function */
    user_delay(period);
}

uint8_t adapter_find_sensors(const struct BUS_INTERFACE_I2C *i2c_ptr, const user_delay_fptr delay_ptr, uint8_t *addresses)
{
    uint8_t no_match = 1;
    uint8_t count = 0;
    uint8_t res = 0;

    for (uint8_t loop_var = 0; loop_var < SENSOR_ADDRESS_SIZE; loop_var++)
    {
        while (no_match && count < max_search_attempts)
        {
            no_match = poll_i2c(i2c_ptr, loop_var, addresses);

            if (no_match){
                count++;
                delay_ptr(10);
            } 
        }

        if(!no_match){
            res++;
        }
        no_match = 1;
        count = 0;
    }
    return res;
}

uint8_t poll_i2c(const struct BUS_INTERFACE_I2C *i2c_ptr, uint8_t loop_var, uint8_t *addresses)
{
    uint8_t sensor_addr = PAC1720_addresses[loop_var];

    uint8_t no_match = i2c_ptr->start((sensor_addr << I2C_ADDRESS_SHIFT) + I2C_WRITE);
    i2c_ptr->stop();

    if(!no_match){
        uint8_t *offset = addresses + loop_var;
        *offset = sensor_addr;
    }
    return no_match;
}

bool sensor_address_out_of_range(const uint8_t address)
{
    if(address == 0x18 || (address > 0x27 && address < 0x2F) || (address > 0x47 && address < 0x50)){
        return false;
    }
    return true;
}

bool channels_out_of_range(const ACTIVE_CHANNELS channels)
{
    if(channels >= FIRST_CHANNEL && channels <= BOTH_CHANNELS){
        return false;
    }
    return true;
}

const void* get_ADAPTER_TEST_FPTR_FIELD(void)
{
    static const void* test_fptr_field[] =  {
                                                 (void*) &adapter_i2c_write,
                                                 (void*) &adapter_i2c_read,
                                                 (void*) &adapter_delay,
                                                 (void*) &sensor_address_out_of_range,
                                                 (void*) &channels_out_of_range,
                                                 (void*) &poll_i2c
                                            };

    return test_fptr_field;
}
