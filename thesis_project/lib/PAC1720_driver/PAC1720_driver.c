/*! @file PAC1720_driver.c
 @brief Sensor driver for PAC1720 sensor */
#include <stdio.h>
#include "PAC1720_driver.h"

/*!
 * @brief This API is used to calculate the Full Scale Current (FSC)
 *
 * This function is used to calculate the Full Scale Current (FSC) of
 * the actual measured channel.  
 * 
 * @note ..
 * @param[in] config	: Pointer to the configuration of one channel.
 *
 * @return Status value.
 * @retval 1 value -> OK/ 0 value -> Error
 */
static int8_t calculate_FSC(struct PAC1720_channel_config *config_ptr);

/*!
 * @brief This API is used to check, whether the device structure is initialized.
 *
 * This function is used to check, whether the device structure is initialized and
 * the contained function pointers are not NULL. 
 * 
 * @note ..
 * @param[in] config	: Pointer to the device struct.
 *
 * @return Status value.
 * @retval 1 value -> OK/ 0 value -> Error
 */
static int8_t device_null_pointer_check(const struct PAC1720_device *device_ptr);

/*!
 * @brief This API is used to calculate the BUS current.
 *
 * This function is used to calculate the BUS current through the
 * sense resistor for both channels, if used.
 * 
 * @note ..
 * @param[in] config	: Pointer to the sensor device struct.
 *
 * @return Status value.
 * @retval 1 value -> OK/ 0 value -> Error
 */
int8_t calculate_BUS_CURRENT(struct PAC1720_device *device_ptr);

int8_t calculate_BUS_CURRENT(struct PAC1720_device *device_ptr)
{   
    int8_t success = PAC1720_FAILURE;
    if(device_null_pointer_check(device_ptr) == PAC1720_FAILURE) return PAC1720_FAILURE;

    if(device_ptr->channel1_active && device_ptr->ch1_readings.reading_done){

        float FSC = device_ptr->sensor_config_ch1.current_sense_FSC;
        float VSENSE= calculate_SENSED_VOLTAGE(&device_ptr->ch1_readings.v_sense_voltage_reg);
        float DENOMINATOR = DENOMINATOR_values_current_sense[device_ptr->sensor_config_ch1.current_sense_sampling_time_reg];
        
        device_ptr->ch1_readings_results.sensed_current = FSC * (VSENSE / DENOMINATOR);
        int8_t success = PAC1720_OK;
    }

    if(device_ptr->channel2_active && device_ptr->ch2_readings.reading_done){

        float FSC = device_ptr->sensor_config_ch2.current_sense_FSC;
        float VSENSE= calculate_SENSED_VOLTAGE(&device_ptr->ch2_readings.v_sense_voltage_reg);
        float DENOMINATOR = DENOMINATOR_values_current_sense[device_ptr->sensor_config_ch2.current_sense_sampling_time_reg];
        
        device_ptr->ch2_readings_results.sensed_current = FSC * (VSENSE / DENOMINATOR);
        int8_t success = PAC1720_OK;
    }

    return success;
}

static float calculate_SENSED_VOLTAGE(uint16_t *v_sense_voltage_ptr)
{
    uint16_t tmp = right_bit_shift(*v_sense_voltage_ptr, zero_LSB);

    if(is_negative_value(&tmp)){

        float result = (float) twos_complement(&tmp);
        return - result;

    } else {
        return (float) tmp;
    } 
}

static uint16_t twos_complement(uint16_t *complement)
{
    uint16_t tmp = ~(*complement);
    return tmp + 0x01;
}

static bool is_negative_value(uint16_t *value)
{
    uint16_t tmp = (*value >> SIGN_BIT);
    if(tmp == 0) return false;
    if(tmp == 1) return true;
}

static uint16_t right_bit_shift(uint16_t *doublebyte, uint8_t shift)
{
    return (*doublebyte >> shift);
}   

static int8_t calculate_FSC(struct PAC1720_channel_config *config_ptr)
{
    if(config_ptr != NULL && config_ptr->current_sense_resistor_value != 0){
        config_ptr->current_sense_FSC = FSR_values[config_ptr->current_sense_FSR_reg] / config_ptr->current_sense_resistor_value;
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

static int8_t device_null_pointer_check(const struct PAC1720_device *device_ptr)
{
    if(device_ptr != NULL || device_ptr->read != NULL || device_ptr->write != NULL || device_ptr->delay_ms != NULL){
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    } 
}
