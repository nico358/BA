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
int8_t create_all_internal_ptrs(struct PAC1720_device *device_ptr, const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay);

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
struct PAC1720_internal * create_internal_ptr(const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay);

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
struct PAC1720_ch_internal * create_ch_internal_ptr(void);

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
struct PAC1720_meas_internal * create_meas_internal_ptr(void);

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
void destroy_all_internal_ptrs(struct PAC1720_device * dev_ptr);

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
void destroy_internal_ptr(struct PAC1720_internal *internal);

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
void destroy_ch_internal_ptr(struct PAC1720_ch_internal *ch_internal);

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
void destroy_meas_internal_ptr(struct PAC1720_meas_internal *meas_internal);

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
int8_t calculate_all_measurements(struct PAC1720_device *device_ptr);

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
int8_t calculate_channel_measurements(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);

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
int8_t set_all_FSx_coefficients(struct PAC1720_device *device_ptr);

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
int8_t set_channel_FSx_coefficients(struct PAC1720_CH_config *config_ptr);


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
void cut_up_limit_registers(struct PAC1720_device *device_ptr);

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
void cut_up_sampling_registers(struct PAC1720_device *device_ptr);

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
void assign_config_register_values(struct PAC1720_device *device_ptr, uint8_t register_field[32]);

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
void assign_reading_register_values(struct PAC1720_device *device_ptr, uint8_t register_field[12]);

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
int8_t read_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len);

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
int8_t write_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len);

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
int8_t calculate_BUS_CURRENT(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);

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
int8_t calculate_BUS_VOLTAGE(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements); 

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
int8_t calculate_BUS_POWER(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);

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
float calculate_SENSED_VOLTAGE(const uint16_t *v_sense_voltage_reg_ptr, const uint8_t *current_sense_sampling_time_reg_ptr);

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
float calculate_SOURCE_VOLTAGE(const uint16_t *v_source_voltage_reg_ptr, const uint8_t *source_voltage_sampling_time_reg_ptr);

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
int8_t calculate_FSC(struct PAC1720_CH_config *config_ptr);

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
int8_t calculate_FSV(struct PAC1720_CH_config *config_ptr);

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
int8_t calculate_FSP(struct PAC1720_ch_internal *ch_internal_ptr);


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
uint16_t combine_bytes(const uint8_t lsb, const uint8_t msb);

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
uint16_t twos_complement(const uint16_t *complement);

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
bool is_negative_value(const uint16_t *value);

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
uint16_t right_bit_shift(const uint16_t *doublebyte, uint8_t shift);

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
int8_t device_null_pointer_check(const struct PAC1720_device *device_ptr);

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
int8_t peripherals_null_pointer_check(const PAC1720_fptr write, const PAC1720_fptr read, const delay_fptr delay);




/******************************** Private data types ******************************************/
/*! Struct holding the calculated Full Scale values of a channel*/
struct 	PAC1720_internal
{
    /* Bus read function pointer */
	PAC1720_fptr read;
	/* Bus write function pointer */
	PAC1720_fptr write;
	/* Delay function pointer */
	delay_fptr 	 delay_ms;

    /* Sensor product id */
	uint8_t      sensor_product_id;
	/* Sensor manufacturer id */
	uint8_t      sensor_manufact_id;
	/* Sensor revision */
	uint8_t      sensor_revision;
};

struct PAC1720_ch_internal
{
    /* Full Scale Current (FSC) */
	float 		current_sense_FSC;
    /* Full Scale Voltage (FSV) */
	float 		source_voltage_FSV;
	/* Full Scale Power (FSP)  */
	float 		power_sense_FSP;
};

struct 	PAC1720_meas_internal
{
    /* Current sense voltage register */
    uint16_t    v_source_voltage_reg;
    /* Source voltage sense register */
    uint16_t    v_sense_voltage_reg;
    /* Power ratio register */
    uint16_t    power_ratio_reg; 
};

/******************************* Function definitions *****************************************/

int8_t init_device_PAC1720(struct PAC1720_device *device_ptr, PAC1720_fptr ext_write, PAC1720_fptr ext_read, delay_fptr ext_delay)
{
    int8_t res = device_null_pointer_check(device_ptr);
    if(res != PAC1720_OK) return res;
    res = peripherals_null_pointer_check(ext_write, ext_read, ext_delay);
    if(res != PAC1720_OK){
        res = create_all_internal_ptrs(device_ptr, ext_write, ext_read, ext_delay);
        if(res != PAC1720_OK) return res;


        // /* Temporary array representation of device registers */
        // uint8_t register_field[32] = {0};
        // /* Read all registers */
        // res = read_registers(device_ptr, configuration_register_address, register_field, GLOBAL_CONFIG_REGISTERS_LENGTH);
        // if(res != PAC1720_OK) return res;
        // res = read_registers(device_ptr, v_source_sampling_configuration_register_address, &register_field[VSOURCE_SAMPLING_REGISTER_OFFSET], CONFIG_READINGS_LIMITS_REGISTERS_LENGTH);
        // if(res != PAC1720_OK) return res;
        // res = read_registers(device_ptr, product_id_register_address, &register_field[SENSOR_INFO_REGISTER_OFFSET], SENSOR_INFO_REGISTER_LENGHT);
        // if(res == PAC1720_OK){
        //     /* Assign local register representation */
        //     assign_config_register_values(device_ptr, register_field);
        //     assign_reading_register_values(device_ptr, &register_field[READING_REGISTERS_OFFSET]);
        //     /* Cut up sample configuration registers on to channel configurations */
        //     cut_up_sampling_registers(device_ptr);
        //     /* Cut up limit registers and check conversion complete bit */
        //     cut_up_limit_registers(device_ptr);
        //     /* Do calculate and set FULL SCALE values. NEED TO BE DONE AT LEAST ONCE after config changes */
        //     res = set_all_FSx_coefficients(device_ptr);
        //     if(res != PAC1720_OK) return res;
        //     if(device_ptr->conversion_cycle_complete){
        //         // /* Do calculation of measurements */
        //         res = calculate_all_measurements(device_ptr);
        //         device_ptr->conversion_cycle_complete = false;
            // }
        // }
    }
    // return res;
}

void destroy_device_PAC1720(struct PAC1720_device *device_ptr)
{
    destroy_all_internal_ptrs(device_ptr);
}

int8_t create_all_internal_ptrs(struct PAC1720_device *device_ptr, const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay)
{
        device_ptr->internal = create_internal_ptr(ext_write, ext_read, ext_delay);
        if(device_ptr->internal == NULL) return PAC1720_INIT_ERROR;

        if(device_ptr->DEV_channels == FIRST_CHANNEL){
            device_ptr->DEV_CH1_conf.ch_internal            = create_ch_internal_ptr();
            device_ptr->DEV_CH1_measurements.meas_internal  = create_meas_internal_ptr();
            if(device_ptr->DEV_CH1_conf.ch_internal == NULL || device_ptr->DEV_CH1_measurements.meas_internal == NULL){ 
                return PAC1720_INIT_ERROR;
            }
            return PAC1720_OK;
        }
        if(device_ptr->DEV_channels == SECOND_CHANNEL){
            device_ptr->DEV_CH2_conf.ch_internal            = create_ch_internal_ptr();
            device_ptr->DEV_CH2_measurements.meas_internal  = create_meas_internal_ptr();
            if(device_ptr->DEV_CH2_conf.ch_internal == NULL || device_ptr->DEV_CH2_measurements.meas_internal == NULL){ 
                return PAC1720_INIT_ERROR;
            }
            return PAC1720_OK;
        }

        device_ptr->DEV_CH1_conf.ch_internal                = create_ch_internal_ptr();
        device_ptr->DEV_CH1_measurements.meas_internal      = create_meas_internal_ptr();
        device_ptr->DEV_CH2_conf.ch_internal                = create_ch_internal_ptr();
        device_ptr->DEV_CH2_measurements.meas_internal      = create_meas_internal_ptr();
        if( device_ptr->DEV_CH1_conf.ch_internal == NULL || device_ptr->DEV_CH1_measurements.meas_internal == NULL || 
            device_ptr->DEV_CH2_conf.ch_internal == NULL || device_ptr->DEV_CH2_measurements.meas_internal == NULL ){
            return PAC1720_INIT_ERROR;
        }
        return PAC1720_OK;
}

struct PAC1720_internal * create_internal_ptr(const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay) 
{
    struct PAC1720_internal * internal = (struct PAC1720_internal *) calloc(1, sizeof(struct PAC1720_internal));
    internal->write     = ext_write;
    internal->read      = ext_read;
    internal->delay_ms  = ext_delay;
    return internal;
}

struct PAC1720_ch_internal * create_ch_internal_ptr(void) 
{
    return (struct PAC1720_ch_internal *) calloc(1, sizeof(struct PAC1720_ch_internal)); 
}

struct PAC1720_meas_internal * create_meas_internal_ptr(void) 
{
    return (struct PAC1720_meas_internal *) calloc(1, sizeof(struct PAC1720_meas_internal)); 
}

void destroy_all_internal_ptrs(struct PAC1720_device * dev_ptr) 
{
    if(dev_ptr->DEV_CH1_measurements.meas_internal != NULL){
        destroy_meas_internal_ptr(dev_ptr->DEV_CH1_measurements.meas_internal);
    }
    if(dev_ptr->DEV_CH2_measurements.meas_internal != NULL){
        destroy_meas_internal_ptr(dev_ptr->DEV_CH2_measurements.meas_internal);
    }
    if(dev_ptr->DEV_CH1_conf.ch_internal != NULL){
        destroy_ch_internal_ptr(dev_ptr->DEV_CH1_conf.ch_internal);
    }
    if(dev_ptr->DEV_CH2_conf.ch_internal != NULL){
        destroy_ch_internal_ptr(dev_ptr->DEV_CH2_conf.ch_internal);
    }
    if(dev_ptr->internal != NULL){
        destroy_internal_ptr(dev_ptr->internal);
    } 
}

void destroy_internal_ptr(struct PAC1720_internal *internal)
{
    internal->read               = NULL;
    internal->write              = NULL;
    internal->delay_ms           = NULL;
    internal->sensor_product_id  = 0;
    internal->sensor_manufact_id = 0;
    internal->sensor_revision    = 0;
    free(internal);
}

void destroy_ch_internal_ptr(struct PAC1720_ch_internal *ch_internal)
{
    ch_internal->current_sense_FSC  = 0;
    ch_internal->source_voltage_FSV = 0;
    ch_internal->power_sense_FSP    = 0;
    free(ch_internal);
}

void destroy_meas_internal_ptr(struct PAC1720_meas_internal *meas_internal)
{
    meas_internal->v_source_voltage_reg = 0;
    meas_internal->v_sense_voltage_reg  = 0;
    meas_internal->power_ratio_reg      = 0;
    free(meas_internal);
}

int8_t read_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len)
{
    uint8_t res = PAC1720_OK;
    struct PAC1720_internal *internal = device_ptr->internal;
    res = internal->read(device_ptr->DEV_sensor_address, reg_address, data_ptr, len); 
    return res;
}

int8_t write_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len)
{
    uint8_t res = PAC1720_OK; 
    struct PAC1720_internal *internal = device_ptr->internal;
    res = internal->write(device_ptr->DEV_sensor_address, reg_address, data_ptr, len);   
    return res;
}

// int8_t get_measurement_registers(struct PAC1720_device *device_ptr)
// {
    // device_ptr->conversion_cycle_complete = false;
    // uint8_t register_field[12] = {0};
    // uint8_t res = PAC1720_FAILURE;
    // res = read_registers(device_ptr, ch1_sense_voltage_high_register_address, register_field, READING_REGISTERS_LENGTH);
    // if(res != PAC1720_OK) return res;
    // assign_reading_register_values(device_ptr, register_field);
    // res = read_registers(device_ptr, high_limit_status_register_address, &device_ptr->high_limit_status_reg, 1);
    // cut_up_limit_registers(device_ptr);
    // if(device_ptr->conversion_cycle_complete){
    // // /* Do calculation of measurements */
    //     res = calculate_all_measurements(device_ptr);
    //     device_ptr->conversion_cycle_complete = false;
    //     return res;
    // } 
    // return res;
// }

int8_t calculate_all_measurements(struct PAC1720_device *device_ptr)
{
    int8_t res = PAC1720_OK;
    if ( device_ptr->DEV_channels == FIRST_CHANNEL && device_ptr->DEV_CH1_measurements.meas_internal != NULL )
    {
        return calculate_channel_measurements(&device_ptr->DEV_CH1_conf, &device_ptr->DEV_CH1_measurements);
    } 
    if ( device_ptr->DEV_channels == SECOND_CHANNEL && device_ptr->DEV_CH2_measurements.meas_internal != NULL)
    { 
        return calculate_channel_measurements(&device_ptr->DEV_CH2_conf, &device_ptr->DEV_CH2_measurements);
    } 
    if( device_ptr->DEV_CH1_measurements.meas_internal != NULL && device_ptr->DEV_CH2_measurements.meas_internal != NULL )
    {
        res = calculate_channel_measurements(&device_ptr->DEV_CH1_conf, &device_ptr->DEV_CH1_measurements);
        if(res != PAC1720_OK) return res;
        return calculate_channel_measurements(&device_ptr->DEV_CH2_conf, &device_ptr->DEV_CH2_measurements);
    }
    return PAC1720_FAILURE;
}

int8_t calculate_channel_measurements(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements)
{
    int8_t res = PAC1720_OK;
    res = calculate_BUS_CURRENT(channel_conf, channel_measurements);
    if(res != PAC1720_OK) return res;
    res = calculate_BUS_VOLTAGE(channel_conf, channel_measurements);
    if(res != PAC1720_OK) return res;
    res = calculate_BUS_POWER(channel_conf, channel_measurements);
    return res;
}

int8_t set_all_FSx_coefficients(struct PAC1720_device *device_ptr)
{
    int8_t res = PAC1720_OK;
    if ( device_ptr->DEV_channels == FIRST_CHANNEL && device_ptr->DEV_CH1_conf.ch_internal != NULL )
    {
        return set_channel_FSx_coefficients(&device_ptr->DEV_CH1_conf);
    } 
    if ( device_ptr->DEV_channels == SECOND_CHANNEL && device_ptr->DEV_CH2_conf.ch_internal != NULL )
    { 
        return set_channel_FSx_coefficients(&device_ptr->DEV_CH2_conf);
    } 
    if(device_ptr->DEV_CH1_conf.ch_internal != NULL && device_ptr->DEV_CH2_conf.ch_internal != NULL )
    {
        res =  set_channel_FSx_coefficients(&device_ptr->DEV_CH1_conf);
        if(res != PAC1720_OK) return res;
        return set_channel_FSx_coefficients(&device_ptr->DEV_CH2_conf);
    }
    return PAC1720_FAILURE;
}

int8_t set_channel_FSx_coefficients(struct PAC1720_CH_config *config_ptr) 
{
    int8_t res = PAC1720_OK;
    res = calculate_FSC(config_ptr);
    if(res != PAC1720_OK) return res;
    res = calculate_FSV(config_ptr);
    if(res != PAC1720_OK) return res;
    res = calculate_FSP(config_ptr->ch_internal);
    return res;
}

void cut_up_limit_registers(struct PAC1720_device *device_ptr)
{
    // device_ptr->DEV_CH1_measurements = (bool) (device_ptr->high_limit_status_reg & BITMASK_CONVERSION_CMPL); 

    /* TODO limit bit eval */
}

void cut_up_sampling_registers(struct PAC1720_device *device_ptr)
{
    // device_ptr->sensor_config_ch2.source_voltage_sampling_time_reg      = (device_ptr->source_voltage_sampling_config_reg    & BITMASK_FIRST_TWO)          >> SHIFT_SIX_BITS;
    // device_ptr->sensor_config_ch2.source_voltage_sampling_average_reg   = (device_ptr->source_voltage_sampling_config_reg    & BITMASK_SECOND_TWO)         >> SHIFT_FOUR_BITS;
    // device_ptr->sensor_config_ch1.source_voltage_sampling_time_reg      = (device_ptr->source_voltage_sampling_config_reg    & BITMASK_THIRD_TWO)          >> SHIFT_TWO_BITS;
    // device_ptr->sensor_config_ch1.current_sense_sampling_average_reg    = device_ptr->source_voltage_sampling_config_reg     & BITMASK_FOURTH_TWO;

    // device_ptr->sensor_config_ch1.current_sense_sampling_time_reg       = (device_ptr->ch1_current_sense_sampling_config_reg & BITMASK_MSB_CURRENT_SAMPLE) >> SHIFT_FOUR_BITS;
    // device_ptr->sensor_config_ch1.current_sense_sampling_average_reg    = (device_ptr->ch1_current_sense_sampling_config_reg & BITMASK_THIRD_TWO)          >> SHIFT_TWO_BITS;
    // device_ptr->sensor_config_ch1.current_sense_FSR_reg                 = device_ptr->ch1_current_sense_sampling_config_reg  & BITMASK_FOURTH_TWO;
    
    // device_ptr->sensor_config_ch2.current_sense_sampling_time_reg       = (device_ptr->ch2_current_sense_sampling_config_reg & BITMASK_MSB_CURRENT_SAMPLE) >> SHIFT_FOUR_BITS;
    // device_ptr->sensor_config_ch2.current_sense_sampling_average_reg    = (device_ptr->ch2_current_sense_sampling_config_reg & BITMASK_THIRD_TWO)          >> SHIFT_TWO_BITS;
    // device_ptr->sensor_config_ch2.current_sense_FSR_reg                 = device_ptr->ch2_current_sense_sampling_config_reg  & BITMASK_FOURTH_TWO;
}

void assign_config_register_values(struct PAC1720_device *device_ptr, uint8_t register_field[32]) 
{
    // device_ptr->configuration_reg                                  = register_field[0];
    // device_ptr->conversion_rate_reg                                = register_field[1];    
    // device_ptr->one_shot_reg                                       = register_field[2];
    // device_ptr->channel_mask_reg                                   = register_field[3];
    // device_ptr->high_limit_status_reg                              = register_field[4];
    // device_ptr->low_limit_status_reg                               = register_field[5];

    // device_ptr->source_voltage_sampling_config_reg                 = register_field[6];
    // device_ptr->ch1_current_sense_sampling_config_reg              = register_field[7];
    // device_ptr->ch2_current_sense_sampling_config_reg              = register_field[8];

    // device_ptr->sensor_config_ch1.current_sense_limit_reg          = combine_bytes(register_field[23], register_field[21]);
    // device_ptr->sensor_config_ch2.current_sense_limit_reg          = combine_bytes(register_field[24], register_field[22]);
    // device_ptr->sensor_config_ch1.source_voltage_limit_reg         = combine_bytes(register_field[27], register_field[25]);
    // device_ptr->sensor_config_ch2.source_voltage_limit_reg         = combine_bytes(register_field[28], register_field[26]);
    // device_ptr->sensor_product_id                                  = register_field[29];
    // device_ptr->sensor_manufact_id                                 = register_field[30];
    // device_ptr->sensor_revision                                    = register_field[31];
}

void assign_reading_register_values(struct PAC1720_device *device_ptr, uint8_t register_field[12]) 
{
    // device_ptr->ch1_readings.v_sense_voltage_reg                   = combine_bytes(register_field[1], register_field[0]);
    // device_ptr->ch2_readings.v_sense_voltage_reg                   = combine_bytes(register_field[3], register_field[2]);
    // device_ptr->ch1_readings.v_source_voltage_reg                  = combine_bytes(register_field[5], register_field[4]);
    // device_ptr->ch2_readings.v_source_voltage_reg                  = combine_bytes(register_field[7], register_field[6]);
    // device_ptr->ch1_readings.power_ratio_reg                       = combine_bytes(register_field[9], register_field[8]);
    // device_ptr->ch2_readings.power_ratio_reg                       = combine_bytes(register_field[11], register_field[10]);
}

int8_t calculate_BUS_CURRENT(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements)
{   
    struct PAC1720_ch_internal   *  internal_config      = &channel_conf->ch_internal;
    struct PAC1720_meas_internal *  internal_measurement = &channel_measurements->meas_internal;
    if(internal_config->current_sense_FSC != 0){

        float FSC = internal_config->current_sense_FSC;
        float Vsense= calculate_SENSED_VOLTAGE(&internal_measurement->v_sense_voltage_reg, &channel_conf->CH_current_sense_sampling_time_reg);
        float DENOMINATOR = DENOMINATOR_values_current_sense[channel_conf->CH_current_sense_sampling_time_reg];
        float Ibus_current = FSC * (Vsense / DENOMINATOR);

        channel_measurements->SENSE_VOLTAGE = Vsense;
        channel_measurements->CURRENT = Ibus_current;
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}
 
int8_t calculate_BUS_VOLTAGE(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements)
{
    struct PAC1720_ch_internal   *  internal_config      = &channel_conf->ch_internal;
    struct PAC1720_meas_internal *  internal_measurement = &channel_measurements->meas_internal;
    if(internal_config->source_voltage_FSV != 0){

        float FSV = internal_config->source_voltage_FSV;
        float Vsource = calculate_SOURCE_VOLTAGE(&internal_measurement->v_source_voltage_reg, &channel_conf->CH_source_voltage_sampling_time_reg);
        float DENOMINATOR = DENOMINATOR_values_source_voltage[channel_conf->CH_source_voltage_sampling_time_reg] - DENOMINATOR_correction_source_voltage;
        float VOLTAGE_source_pin = FSV * (Vsource / DENOMINATOR);
        
        channel_measurements->SOURCE_VOLTAGE = VOLTAGE_source_pin;
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

int8_t calculate_BUS_POWER(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements)
{
    struct PAC1720_ch_internal   * internal_config  = &channel_conf->ch_internal;
    struct PAC1720_meas_internal * internal_meas    = &channel_measurements->meas_internal;

    if(internal_config->power_sense_FSP != 0){
        
        float FSP = internal_config->power_sense_FSP;
        float Pratio = (float) internal_meas->power_ratio_reg;
        float Pbus_power = FSP * (Pratio / 65535.0f);

        channel_measurements->POWER = Pbus_power;
        
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

float calculate_SENSED_VOLTAGE(const uint16_t *v_sense_voltage_reg_ptr, const uint8_t *current_sense_sampling_time_reg_ptr)
{
    uint16_t tmp = right_bit_shift(v_sense_voltage_reg_ptr, CURRENT_RESOLUTION_IGNORE_BITS[*current_sense_sampling_time_reg_ptr]);

    if(is_negative_value(v_sense_voltage_reg_ptr)){

        uint16_t complement = twos_complement(&tmp);
        tmp = complement & NEGATIVE_CURRENT_RESOLUTION_MASK[*current_sense_sampling_time_reg_ptr];
        float res = (float) tmp;

        return - res;
    } else {
        return (float) tmp;
    } 
}

float calculate_SOURCE_VOLTAGE(const uint16_t *v_source_voltage_reg_ptr, const uint8_t *source_voltage_sampling_time_reg_ptr)
{
    return (float) right_bit_shift(v_source_voltage_reg_ptr, VSOURCE_RESOLUTION_IGNORE_BITS[*source_voltage_sampling_time_reg_ptr]);
}

int8_t calculate_FSC(struct PAC1720_CH_config *config_ptr) 
{
    if(config_ptr->CH_current_sense_resistor_value != 0 && config_ptr->ch_internal != NULL && config_ptr != NULL){
        struct PAC1720_ch_internal *ch_internal_ptr = config_ptr->ch_internal;

        float FSR = FSR_values[config_ptr->CH_current_sense_FSR_reg];
        float RESISTANCE = config_ptr->CH_current_sense_resistor_value;

        ch_internal_ptr->current_sense_FSC = FSR / RESISTANCE;

        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

int8_t calculate_FSV(struct PAC1720_CH_config *config_ptr) 
{
    if(config_ptr->ch_internal != NULL && config_ptr != NULL){
        struct PAC1720_ch_internal *ch_internal_ptr = config_ptr->ch_internal;

        float DENOMINATOR = DENOMINATOR_values_source_voltage[config_ptr->CH_source_voltage_sampling_time_reg];

        ch_internal_ptr->source_voltage_FSV = 40 - (40 / DENOMINATOR);

        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

int8_t calculate_FSP(struct PAC1720_ch_internal *ch_internal_ptr) 
{
    if(ch_internal_ptr != NULL && ch_internal_ptr->current_sense_FSC != 0 && ch_internal_ptr->source_voltage_FSV != 0){

        ch_internal_ptr->power_sense_FSP = ch_internal_ptr->current_sense_FSC * ch_internal_ptr->source_voltage_FSV;

        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

uint16_t combine_bytes(const uint8_t lsb, const uint8_t msb)
{
    return (msb << SHIFT_IN_BYTES_OFFSET) + lsb;
}

uint16_t twos_complement(const uint16_t *to_complement)
{
    uint16_t tmp = ~(*to_complement);
    return tmp + 0x01;
}

bool is_negative_value(const uint16_t *value)
{
    return (bool) right_bit_shift(value, SHIFT_TO_SIGN_BIT);
}

uint16_t right_bit_shift(const uint16_t *doublebyte, const uint8_t shift)
{
    return (uint16_t)(*doublebyte >> shift);
}   

int8_t peripherals_null_pointer_check(const PAC1720_fptr write, const PAC1720_fptr read, const delay_fptr delay)
{
    if(write != NULL && read != NULL && delay != NULL){
        return PAC1720_OK; 
    } else {
        return PAC1720_NULLPTR_ERROR;
    } 
}

int8_t device_null_pointer_check(const struct PAC1720_device *device_ptr) 
{
    if(device_ptr != NULL){
        return PAC1720_OK; 
    } else {
        return PAC1720_NULLPTR_ERROR;
    } 
}


const void* get_TEST_DRIVER_FPTR_FIELD(void)
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
                                                 (void*) &write_registers,
                                                 (void*) &assign_config_register_values,
                                                 (void*) &assign_reading_register_values,
                                                 (void*) &combine_bytes,
                                                 (void*) &cut_up_sampling_registers,
                                                 (void*) &cut_up_limit_registers,
                                                 (void*) &create_internal_ptr,
                                                 (void*) &create_ch_internal_ptr,
                                                 (void*) &destroy_internal_ptr,
                                                 (void*) &destroy_ch_internal_ptr,
                                                 (void*) &peripherals_null_pointer_check,
                                                 (void*) &create_meas_internal_ptr,
                                                 (void*) &destroy_meas_internal_ptr
                                            };

    return &test_fptr_field;
}
