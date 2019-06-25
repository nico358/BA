/*! @file PAC1720_driver.c
*   @brief Sensor driver for PAC1720 sensor 
 */
#include "PAC1720_driver.h"

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
static int8_t read_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len);

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
static int8_t write_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len);

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
static int8_t calculate_BUS_CURRENT(const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings);

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
static int8_t calculate_BUS_VOLTAGE(const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings);

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
static int8_t calculate_BUS_POWER(const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings);

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
static float calculate_SENSED_VOLTAGE(const uint16_t *v_sense_voltage_reg_ptr, const uint8_t *current_sense_sampling_time_reg_ptr);

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
static float calculate_SOURCE_VOLTAGE(const uint16_t *v_source_voltage_reg_ptr, const uint8_t *source_voltage_sampling_time_reg_ptr);

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
static int8_t calculate_FSC(struct PAC1720_channel_config *config_ptr);

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
static int8_t calculate_FSV(struct PAC1720_channel_config *config_ptr);

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
static int8_t calculate_FSP(struct PAC1720_channel_config *config_ptr);

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
static uint16_t twos_complement(const uint16_t *complement);

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
static bool is_negative_value(const uint16_t *value);

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
static uint16_t right_bit_shift(const uint16_t *doublebyte, uint8_t shift);

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
static int8_t device_null_pointer_check(const struct PAC1720_device *device_ptr);


/******************************* Function definitions *****************************************/

int8_t init_device_PAC1720(struct PAC1720_device *dev)
{
    if(device_null_pointer_check(dev) == 0){
        
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

static int8_t read_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len)
{
    uint8_t res = PAC1720_OK;
    if(device_null_pointer_check(device_ptr) == 0){
        res = device_ptr->read(device_ptr->sensor_address, reg_address, data_ptr, len);   
        return res;
    } else {
        return PAC1720_FAILURE;
    }
}

static int8_t write_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len)
{
    uint8_t res = PAC1720_OK; 
    if(device_null_pointer_check(device_ptr) == 0){
        res = device_ptr->write(device_ptr->sensor_address, reg_address, data_ptr, len);   
        return res;
    } else {
        return PAC1720_FAILURE;
    }
}

static int8_t calculate_BUS_CURRENT(const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings)
{   
    if(channel_readings->reading_done && channel_conf->current_sense_FSC != 0){

        float FSC = channel_conf->current_sense_FSC;
        float Vsense= calculate_SENSED_VOLTAGE(&channel_readings->v_sense_voltage_reg, &channel_conf->current_sense_sampling_time_reg);
        float DENOMINATOR = DENOMINATOR_values_current_sense[channel_conf->current_sense_sampling_time_reg];
        float Ibus_current = FSC * (Vsense / DENOMINATOR);

        channel_readings->res_SENSE_VOLTAGE = Vsense;
        channel_readings->res_CURRENT = Ibus_current;
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

static int8_t calculate_BUS_VOLTAGE(const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings)
{
    if(channel_readings->reading_done && channel_conf->source_voltage_FSV != 0){

        float FSV = channel_conf->source_voltage_FSV;
        float Vsource = calculate_SOURCE_VOLTAGE(&channel_readings->v_source_voltage_reg, &channel_conf->source_voltage_sampling_time_reg);
        float DENOMINATOR = DENOMINATOR_values_source_voltage[channel_conf->source_voltage_sampling_time_reg] - DENOMINATOR_correction_source_voltage;
        float VOLTAGE_source_pin = FSV * (Vsource / DENOMINATOR);
        
        channel_readings->res_SOURCE_VOLTAGE = VOLTAGE_source_pin;
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

static int8_t calculate_BUS_POWER(const struct PAC1720_channel_config *channel_conf, struct PAC1720_channel_readings *channel_readings)
{
    if(channel_readings->reading_done && channel_conf->power_sense_FSP != 0){
        
        float FSP = channel_conf->power_sense_FSP;
        float Pratio = (float) channel_readings->power_ratio_reg;
        float Pbus_power = FSP * (Pratio / 65535.0f);

        channel_readings->res_POWER = Pbus_power;
        
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

static float calculate_SENSED_VOLTAGE(const uint16_t *v_sense_voltage_reg_ptr, const uint8_t *current_sense_sampling_time_reg_ptr)
{
    uint16_t tmp = right_bit_shift(v_sense_voltage_reg_ptr, CURRENT_RESOLUTION_IGNORE_BITS[*current_sense_sampling_time_reg_ptr]);

    if(is_negative_value(v_sense_voltage_reg_ptr)){
        
        uint16_t complement = twos_complement(&tmp);
        tmp = complement & NEGATIVE_CURRENT_RESOLUTION_MASK[*current_sense_sampling_time_reg_ptr];
        return (float) - tmp;

    } else {
        return (float) tmp;
    } 
}

static float calculate_SOURCE_VOLTAGE(const uint16_t *v_source_voltage_reg_ptr, const uint8_t *source_voltage_sampling_time_reg_ptr)
{
    return (float) right_bit_shift(v_source_voltage_reg_ptr, VSOURCE_RESOLUTION_IGNORE_BITS[*source_voltage_sampling_time_reg_ptr]);
}

static int8_t calculate_FSC(struct PAC1720_channel_config *config_ptr) 
{
    if(config_ptr != NULL && config_ptr->current_sense_resistor_value != 0){

        float FSR = FSR_values[config_ptr->current_sense_FSR_reg];
        float RESISTANCE = config_ptr->current_sense_resistor_value;

        config_ptr->current_sense_FSC = FSR / RESISTANCE;

        return PAC1720_OK;

    } else {
        return PAC1720_FAILURE;
    }
}

static int8_t calculate_FSV(struct PAC1720_channel_config *config_ptr)
{
    if(config_ptr != NULL){

        float DENOMINATOR = DENOMINATOR_values_source_voltage[config_ptr->source_voltage_sampling_time_reg];
        config_ptr->source_voltage_FSV = 40 - (40 / DENOMINATOR);

        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

static int8_t calculate_FSP(struct PAC1720_channel_config *config_ptr)
{
    if(config_ptr != NULL && config_ptr->current_sense_FSC != 0 && config_ptr->source_voltage_FSV != 0){

        config_ptr->power_sense_FSP = config_ptr->current_sense_FSC * config_ptr->source_voltage_FSV;

        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

static uint16_t twos_complement(const uint16_t *to_complement)
{
    uint16_t tmp = ~(*to_complement);
    return tmp + 0x01;
}

static bool is_negative_value(const uint16_t *value)
{
    return (bool) right_bit_shift(value, SHIFT_TO_SIGN_BIT);
}

static uint16_t right_bit_shift(const uint16_t *doublebyte, const uint8_t shift)
{
    return (uint16_t)(*doublebyte >> shift);
}   

static int8_t device_null_pointer_check(const struct PAC1720_device *device_ptr)
{
    if(device_ptr != NULL && device_ptr->read != NULL && device_ptr->write != NULL && device_ptr->delay_ms != NULL){
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    } 
}

const void* get_TEST_FPTR_FIELD(void)
{
    static const void* test_fptr_field[] =  {
                                                 (void*) &calculate_BUS_CURRENT,
                                                 (void*) &calculate_SENSED_VOLTAGE,
                                                 (void*) &calculate_FSC,
                                                 (void*) &twos_complement,
                                                 (void*) &is_negative_value,
                                                 (void*) &right_bit_shift,
                                                 (void*) &device_null_pointer_check,
                                                 (void*) &calculate_BUS_VOLTAGE,
                                                 (void*) &calculate_SOURCE_VOLTAGE,
                                                 (void*) &calculate_FSV,
                                                 (void*) &calculate_BUS_POWER,
                                                 (void*) &calculate_FSP,
                                                 (void*) &read_registers,
                                                 (void*) &write_registers
                                            };

    return test_fptr_field;
}
