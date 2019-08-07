/*! @file PAC1720_driver.c
 @brief Sensor driver for PAC1720 sensor */
/*!
 * @defgroup PAC1720 driver API
 * @{*/

#include "PAC1720_driver.h"

/*!
 * @fn set_sensor_to_sleep
 * 
 * @brief Sets the sensor to sleep mode. Deactivates all measurements.
 *
 * @param[in] device_ptr :  Pointer to structure instance of sensor.
 *
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t set_sensor_to_sleep(struct PAC1720_device *device_ptr);

/*!
 * @fn sensor_is_in_sleep
 * 
 * @brief Gets the actual state of the sensor.
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 *
 * @return Sensors operation state.
 * @retval true -> sensor sleeps / false -> sensor operates
 */
bool sensor_is_in_sleep(struct PAC1720_device *device_ptr);

/*!
 * @fn check_name_opt
 * 
 * @brief Checks if a name is provided in struct instance of sensor and set default name if not. 
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 *
 */
void check_name_opt(struct PAC1720_device *device_ptr);

/*!
 * @fn write_all_settings_to_sensor
 * 
 * @brief Writes the configuration stored in the struct instance to the sensor.
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 *
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t write_all_settings_to_sensor(struct PAC1720_device *device_ptr);

/*!
 * @fn write_out_global_config_registers
 * 
 * @brief Writes the global configuration stored in the struct instance to the sensor.
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 *
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t write_out_global_config_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_tmp_global_config_array
 * 
 * @brief Helper function to create an array of data for the bus write function.
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_config_reg : Array holding the global configration settings temporary.
 *
 */
void assign_tmp_global_config_array(struct PAC1720_device *device_ptr, uint8_t tmp_config_reg[4]);

/*!
 * @fn write_out_sampling_config_registers
 * 
 * @brief Writes the sampling configuration stored in the struct instance to the sensor.
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 *
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t write_out_sampling_config_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_tmp_sampling_config_array
 * 
 * @brief Helper function to create an array of data for the bus write function.
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_smpl_conf_reg : Array holding the sampling configuration settings temporary.
 *
 */
void assign_tmp_sampling_config_array(struct PAC1720_device *device_ptr, uint8_t tmp_smpl_conf_reg[3]);

/*!
 * @fn write_out_limit_registers
 * 
 * @brief Writes the limit configuration stored in the struct instance to the sensor.
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 *
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t write_out_limit_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_tmp_limit_array
 * 
 * @brief Helper function to create an array of data for the bus write function.
 *
 * @param[in] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_lmt_reg : Array holding the limit configuration settings temporary.
 *
 */
void assign_tmp_limit_array(struct PAC1720_device *device_ptr, uint8_t tmp_lmt_reg[8]);

/*!
 * @fn get_all_settings_from_sensor
 * 
 * @brief Gets the current configuration from the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 *
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t get_all_settings_from_sensor(struct PAC1720_device *device_ptr);

/*!
 * @fn readin_global_config_registers
 * 
 * @brief Reads the global config settings from the sensor into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t readin_global_config_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_global_config_registers
 * 
 * @brief Helper function to write the data from temporary array of the bus read function into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_config_reg : Array holding the global configuration configuration settings temporary.
 *
 */
void assign_global_config_registers(struct PAC1720_device *device_ptr, uint8_t tmp_config_reg[4]);

/*!
 * @fn readin_limit_status_registers
 * 
 * @brief Reads the limit status registers from the sensor into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t readin_limit_status_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_limit_status_registers
 * 
 * @brief Helper function to write the data from temporary array of the bus read function into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_smpl_conf_reg : Array holding the status limit settings temporary.
 *
 */
void assign_limit_status_registers(struct PAC1720_device *device_ptr, uint8_t tmp_smpl_conf_reg[3]);

/*!
 * @fn readin_sampling_config_registers
 * 
 * @brief Reads the sampling config registers from the sensor into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t readin_sampling_config_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_sampling_config_registers
 * 
 * @brief Helper function to write the data from temporary array of the bus read function into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_smpl_conf_reg : Array holding the sampling settings temporary.
 *
 */
void assign_sampling_config_registers(struct PAC1720_device *device_ptr, uint8_t tmp_smpl_conf_reg[3]);

/*!
 * @fn readin_measurements_registers
 * 
 * @brief Reads the measurements registers from the sensor into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t readin_measurements_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_internal_measurements_registers
 * 
 * @brief Helper function to write the data from temporary array of the bus read function into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_meas_reg : Array holding the sensor measurement results temporary.
 *
 */
void assign_internal_measurements_registers(struct PAC1720_device *device_ptr, uint8_t tmp_meas_reg[12]);

/*!
 * @fn set_measurements_zero
 * 
 * @brief Helper function to reset all measurements in the struct.
 * 
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 */
void set_measurements_zero(struct PAC1720_device *device_ptr);

/*!
 * @fn readin_limit_registers
 * 
 * @brief Reads the limit registers from the sensor into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t readin_limit_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_ch_limit_registers
 * 
 * @brief Helper function to write the data from temporary array of the bus read function into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_lmt_reg : Array holding the limit registers temporary.
 *
 */
void assign_ch_limit_registers(struct PAC1720_device *device_ptr, uint8_t tmp_lmt_reg[8]);

/*!
 * @fn readin_sensor_infos_registers
 * 
 * @brief Reads the info registers from the sensor into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t readin_sensor_infos_registers(struct PAC1720_device *device_ptr);

/*!
 * @fn assign_sensor_infos_registers
 * 
 * @brief Helper function to write the data from temporary array of the bus read function into the struct instance of the sensor.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] tmp_read : Array holding the info registers temporary.
 *
 */
void assign_sensor_infos_registers(struct PAC1720_internal *internal, uint8_t tmp_read[3]);

/*!
 * @fn create_all_internal_ptrs
 * 
 * @brief Assigns all internal pointers in the sensor struct instance.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] ext_write : Pointer to the user defined bus write function.
 * @param[in] ext_read : Pointer to the user defined bus read function.
 * @param[in] ext_delay : Pointer to the user defined delay function.
 * 
 * @see adapter_PAC1720.h
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t create_all_internal_ptrs(struct PAC1720_device *device_ptr, const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay);

/*!
 * @fn create_internal_ptr
 * 
 * @brief Allocates memory for internal pointer of the sensor struct instance and assigns peripheral pointers to the struct.
 *
 * @param[in] ext_write : Pointer to the user defined bus write function.
 * @param[in] ext_read : Pointer to the user defined bus read function.
 * @param[in] ext_delay : Pointer to the user defined delay function.
 * 
 * @see PAC1720_internal.
 * 
 * @return Pointer to allocated memory for PAC1720_internal struct.
 * @retval Pointer.
 */
struct PAC1720_internal * create_internal_ptr(const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay);

/*!
 * @fn create_ch_internal_ptr
 * 
 * @brief Allocates memory for the internal channel configuration pointer of the sensor struct instance.
 * 
 * @see PAC1720_ch_internal.
 * 
 * @return Pointer to allocated memory for PAC1720_ch_internal struct.
 * @retval Pointer.
 */
struct PAC1720_ch_internal * create_ch_internal_ptr(void);

/*!
 * @fn create_meas_internal_ptr
 * 
 * @brief Allocates memory for the internal measurement pointer of the sensor struct instance.
 * 
 * @see PAC1720_meas_internal.
 * 
 * @return Pointer to allocated memory for PAC1720_meas_internal struct.
 * @retval Pointer.
 */
struct PAC1720_meas_internal * create_meas_internal_ptr(void);

/*!
 * @fn destroy_all_internal_ptrs
 * 
 * @brief Frees all memory allocated to internal pointers in the sensor struct instance.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 */
void destroy_all_internal_ptrs(struct PAC1720_device * dev_ptr);

/*!
 * @fn destroy_all_internal_ptrs
 * 
 * @brief Frees memory allocated to the internal pointer in the sensor struct instance and sets values to zero.
 *
 * @param[in/out] internal : Pointer to internal struct instance of sensor.
 * 
 */
void destroy_internal_ptr(struct PAC1720_internal *internal);

/*!
 * @fn destroy_ch_internal_ptr
 * 
 * @brief Frees memory allocated to the channel internal pointer in the sensor struct instance and sets values to zero.
 *
 * @param[in/out] ch_internal : Pointer to internal channel struct instance of sensor.
 * 
 */
void destroy_ch_internal_ptr(struct PAC1720_ch_internal *ch_internal);

/*!
 * @fn destroy_meas_internal_ptr
 * 
 * @brief Frees memory allocated to the channel measurement internal pointer in the sensor struct instance and sets values to zero.
 *
 * @param[in/out] meas_internal : Pointer to internal measurement struct instance of sensor.
 * 
 */
void destroy_meas_internal_ptr(struct PAC1720_meas_internal *meas_internal);

/*!
 * @fn calculate_all_measurements
 * 
 * @brief Calculate all actual values from sensor measurement results.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t calculate_all_measurements(struct PAC1720_device *device_ptr);

/*!
 * @fn calculate_channel_measurements
 * 
 * @brief Calculate actual values for a channel from sensor measurement results.
 *
 * @param[in] channel_conf : Pointer to channel config structure instance of sensor.
 * @param[in/out] channel_measurements : Pointer to measurement structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t calculate_channel_measurements(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);

/*!
 * @fn calculate_channel_measurements
 * 
 * @brief Calculates all Full Scale values for sensor channels.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t set_all_FSx_coefficients(struct PAC1720_device *device_ptr);

/*!
 * @fn set_channel_FSx_coefficients
 * 
 * @brief Calculates all Full Scale values for a single sensor channel.
 *
 * @param[in/out] config_ptr : Pointer to channel configuration structure instance of sensor.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t set_channel_FSx_coefficients(struct PAC1720_CH_config *config_ptr);

/*!
 * @fn read_registers
 * 
 * @brief Internal bus read function.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] reg_address : Address of the sensor register to be read from.
 * @param[in/out] data_ptr : Pointer to the data structure where the data are to be read in.
 * @param[in] len : Lenght of data_ptr in bytes.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t read_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len);

/*!
 * @fn write_registers
 * 
 * @brief Internal bus write function.
 *
 * @param[in/out] device_ptr : Pointer to structure instance of sensor.
 * @param[in] reg_address : Address of the sensor register to be written.
 * @param[in/out] data_ptr : Pointer to the data structure where the data are to be written from.
 * @param[in] len : Lenght of data_ptr in bytes.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t write_registers(const struct PAC1720_device *device_ptr, uint8_t reg_address, uint8_t *data_ptr, uint8_t len);

/*!
 * @fn calculate_BUS_CURRENT
 * 
 * @brief Calculates the actual current for a channel from the sensor results.
 *
 * @param[in] channel_conf : Pointer to channel configuration structure instance of sensor.
 * @param[in/out] channel_measurements : Pointer to the channel measurement structure that holds the results.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t calculate_BUS_CURRENT(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);

/*!
 * @fn calculate_BUS_VOLTAGE
 * 
 * @brief Calculates the actual source voltage for a channel from the sensor results.
 *
 * @param[in] channel_conf : Pointer to channel configuration structure instance of sensor.
 * @param[in/out] channel_measurements : Pointer to the channel measurement structure that holds the results.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t calculate_BUS_VOLTAGE(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements); 

/*!
 * @fn calculate_BUS_POWER
 * 
 * @brief Calculates the actual power for a channel from the sensor results.
 *
 * @param[in] channel_conf : Pointer to channel configuration structure instance of sensor.
 * @param[in/out] channel_measurements : Pointer to the channel measurement structure that holds the results.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t calculate_BUS_POWER(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements);

/*!
 * @fn calculate_SENSED_VOLTAGE
 * 
 * @brief Calculates the differential (sense) voltage for a channel from the sensor results.
 *
 * @param[in] v_sense_voltage_reg_ptr : Pointer to the sense voltage result (internal measurement struct) of a measurement.
 * @param[in] current_sense_sampling_time_reg_ptr : Pointer to the current sampling time in channel configuration.
 * 
 * @return Sense voltage.
 */
float calculate_SENSED_VOLTAGE(const uint16_t *v_sense_voltage_reg_ptr, const uint8_t *current_sense_sampling_time_reg_ptr);

/*!
 * @fn calculate_SOURCE_VOLTAGE
 * 
 * @brief Calculates the source voltage for a channel from the sensor results.
 *
 * @param[in] v_source_voltage_reg_ptr : Pointer to the source voltage result (internal measurement struct) of a measurement.
 * @param[in] source_voltage_sampling_time_reg_ptr : Pointer to the source voltage sampling time in channel configuration.
 * 
 * @return Source voltage.
 */
float calculate_SOURCE_VOLTAGE(const uint16_t *v_source_voltage_reg_ptr, const uint8_t *source_voltage_sampling_time_reg_ptr);

/*!
 * @fn calculate_FSC
 * 
 * @brief Calculates the FSC for a channel.
 *
 * @param[in/out] config_ptr : Pointer to the channel configuration structure.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t calculate_FSC(struct PAC1720_CH_config *config_ptr);

/*!
 * @fn calculate_FSV
 * 
 * @brief Calculates the FSV for a channel.
 *
 * @param[in/out] config_ptr : Pointer to the channel configuration structure.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t calculate_FSV(struct PAC1720_CH_config *config_ptr);

/*!
 * @fn calculate_FSP
 * 
 * @brief Calculates the FSP for a channel.
 *
 * @param[in/out] ch_internal_ptr : Pointer to the internal channel configuration structure.
 * 
 * @return Success or failure.
 * @retval 0 value -> OK/ !=0 value -> Error
 */
int8_t calculate_FSP(struct PAC1720_ch_internal *ch_internal_ptr);


/*!
 * @fn combine_bytes
 * 
 * @brief Helper function to shift two 8 bit values in a 16 bit value.
 *
 * @param[in] lsb : Least significant byte.
 * @param[in] msb : Most significant byte.
 * 
 * @return 16 bit value.
 */
uint16_t combine_bytes(const uint8_t *lsb, const uint8_t *msb);

/*!
 * @fn twos_complement
 * 
 * @brief Helper function to get the two's complement from a 16 bit value.
 *
 * @param[in] complement : Value to complement.
 * 
 * @return The two's complement of the input.
 */
uint16_t twos_complement(const uint16_t *complement);

/*!
 * @fn is_negative_value
 * 
 * @brief Helper function to get the sign bit of a 16 bit value.
 *
 * @param[in] value : Value to check.
 * 
 * @return The 16th bit.
 * @retval 1 value -> negative/ 0 value -> positive
 */
bool is_negative_value(const uint16_t *value);

/*!
 * @fn right_bit_shift
 * 
 * @brief Helper function to shift bits in a 16 bit value.
 *
 * @param[in] doublebyte : Value to shift.
 * @param[in] shift : Number of bits to shift.
 * 
 * @return The shifted value.
 */
uint16_t right_bit_shift(const uint16_t *doublebyte, uint8_t shift);

/*!
 * @fn device_null_pointer_check
 * 
 * @brief Helper function to control if struct internal pointers are allocated.
 *
 * @param[in] device_ptr : Pointer to the device structure.
 * 
 * @retval 0 value -> success/ !=0 value -> error
 */
int8_t device_null_pointer_check(const struct PAC1720_device *device_ptr);

/*!
 * @fn peripherals_null_pointer_check
 * 
 * @brief Helper function to control if external provided pointers are allocated.
 *
 * @param[in] write : Pointer to the external bus write function.
 * @param[in] read : Pointer to the external bus read function.
 * @param[in] delay : Pointer to the external delay function.
 * 
 * @retval 0 value -> success/ !=0 value -> error
 */
int8_t peripherals_null_pointer_check(const PAC1720_fptr write, const PAC1720_fptr read, const delay_fptr delay);

/*!
 * @fn first_channel_is_active
 * 
 * @brief Helper function to check if first measurement channel is active or disabled.
 *
 * @param[in] device_ptr : Pointer to the device structure.
 * 
 * @retval true -> active/ false -> disabled
 */
bool first_channel_is_active(const struct PAC1720_device *device_ptr);

/*!
 * @fn second_channel_is_active
 * 
 * @brief Helper function to check if second measurement channel is disabled.
 *
 * @param[in] device_ptr : Pointer to the device structure.
 * 
 * @retval true -> active/ false -> disabled
 */
bool second_channel_is_active(const struct PAC1720_device *device_ptr);




/******************************** Private data types ******************************************/

/* Structure definitions */
/*!
 * @brief  Datastructures that are holding private data. 
 */
/*! Struct holding the pointers to bus communication fuctions, delay function and  sensor information */
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

/*! Struct holding theFull Scale values of a channel */
struct PAC1720_ch_internal
{
    /* Full Scale Current (FSC) */
	float 		current_sense_FSC;
    /* Full Scale Voltage (FSV) */
	float 		source_voltage_FSV;
	/* Full Scale Power (FSP)  */
	float 		power_sense_FSP;
};

/*! Struct holding the sensors measurement results of a channel */
struct 	PAC1720_meas_internal
{
    /* Current sense voltage register */
    uint16_t    v_source_voltage_reg;
    /* Source voltage sense register */
    uint16_t    v_sense_voltage_reg;
    /* Power ratio register */
    uint16_t    power_ratio_reg; 
};

/******************************* Public function definitions *****************************************/

/*!
 * @brief Initializes the internal struct instance with the config from the sensor.
 */
int8_t init_device_PAC1720_from_field(struct PAC1720_device *device_ptr, PAC1720_fptr ext_write, PAC1720_fptr ext_read, delay_fptr ext_delay)
{
    /* Check if provided pointers valid */
    int8_t res = device_null_pointer_check(device_ptr);
    if(res != PAC1720_OK) return res;
    res = peripherals_null_pointer_check(ext_write, ext_read, ext_delay);
    if(res == PAC1720_OK)
    {   
        /* Destroy all current internal pointers, reset measurements and set name to default if none is provided */
        destroy_all_internal_ptrs(device_ptr);
        set_measurements_zero(device_ptr);
        check_name_opt(device_ptr);
        /* Create all pointers */
        res = create_all_internal_ptrs(device_ptr, ext_write, ext_read, ext_delay);
        if(res != PAC1720_OK) return res;
        /* Read the settings from sensor */
        res = get_all_settings_from_sensor(device_ptr);
        if(res != PAC1720_OK) return res;
        /* Calculate all Full Scale Values from provided configuration */
        res = set_all_FSx_coefficients(device_ptr);
    }
    return res;
}

/*!
 * @brief Initializes the sensor with the config from internal struct.
 */
int8_t init_device_PAC1720_user_defined(struct PAC1720_device *device_ptr, PAC1720_fptr ext_write, PAC1720_fptr ext_read, delay_fptr ext_delay)
{
    /* Check if provided pointers valid */
    int8_t res = device_null_pointer_check(device_ptr);
    if(res != PAC1720_OK) return res;
    res = peripherals_null_pointer_check(ext_write, ext_read, ext_delay);
    if(res == PAC1720_OK)
    {   
        /* Destroy all current internal pointers, reset measurements and set name to default if none is provided */
        destroy_all_internal_ptrs(device_ptr);
        set_measurements_zero(device_ptr);
        check_name_opt(device_ptr);
        /* Create all pointers */
        res = create_all_internal_ptrs(device_ptr, ext_write, ext_read, ext_delay);
        /* Set sleep mode to allow writing the config registers of the sensor */
        if(res != PAC1720_OK) return res;
        res = set_sensor_to_sleep(device_ptr);
        if(res != PAC1720_OK) return res;
        /* Poll sensor state and return error if sensor ins't sleeping after MAX_ATTEMPTS_SET_SLEEP_MODE */
        uint16_t cnt = 0;
        while(!sensor_is_in_sleep(device_ptr)){
            if(cnt == MAX_ATTEMPTS_SET_SLEEP_MODE) 
                return PAC1720_INIT_ERROR;
            cnt++;
        };
        /* Configure the sensor */
        res = write_all_settings_to_sensor(device_ptr);
        if(res != PAC1720_OK) return res;
        /* Assign sensor information to internal struct instance */
        res = readin_sensor_infos_registers(device_ptr);
        if(res != PAC1720_OK) return res;
        /* Calculate all Full Scale Values from provided configuration */
        res = set_all_FSx_coefficients(device_ptr);
    }
    return res;
}

/*!
 * @brief Free all allocated memory and reset values of internal struct pointers.
 */
void destroy_device_PAC1720(struct PAC1720_device *device_ptr)
{
    destroy_all_internal_ptrs(device_ptr);
}

/*!
 * @brief Fetch the measurement results from sensor and calculate actual values.
 */
int8_t get_all_measurements_PAC1720(struct PAC1720_device *device_ptr)
{
    /* Null pointer check */
    if(device_ptr->internal == NULL) return PAC1720_NULLPTR_ERROR;
    int8_t res = PAC1720_OK;
    /* Read the limit statuses of the sensor (conversion cycle done flag) */
    res = readin_limit_status_registers(device_ptr);
    if(res != PAC1720_OK) return res;
    /* Check if sensor conversion cycle flag of sensor is set */
    if(device_ptr->DEV_CH1_measurements.conversion_done || device_ptr->DEV_CH2_measurements.conversion_done)
    {
        /* Fetch mesaurement results from sensor and calculate actual values */
        res = readin_measurements_registers(device_ptr);
        if(res != PAC1720_OK) return res;
        res = calculate_all_measurements(device_ptr);
    }
    else
    {
        /* If sensor hasn't finished conversion reset measurements to avoid wrong results*/
        set_measurements_zero(device_ptr);
        return PAC1720_CONVERSION_UNDONE;
    }
    return res;
}

/*!
 * @brief Fetch the measurement results from sensor but don't calculate actual values.
 */
int8_t get_raw_measurements_PAC1720(struct PAC1720_device *device_ptr)
{
    /* Null pointer check */
    if(device_ptr->internal == NULL) return PAC1720_NULLPTR_ERROR;
    int8_t res = PAC1720_OK;
    /* Read the limit statuses of the sensor (conversion cycle done flag) */
    res = readin_limit_status_registers(device_ptr);
    if(res != PAC1720_OK) return res;
    /* Check if sensor conversion cycle flag of sensor is set */
    if(device_ptr->DEV_CH1_measurements.conversion_done || device_ptr->DEV_CH2_measurements.conversion_done)
    {
        /* Fetch mesaurement results from sensor and calculate actual values */
        res = readin_measurements_registers(device_ptr);
        if(res != PAC1720_OK) return res;
    }
    /* If sensor hasn't finished conversion reset measurements to avoid wrong results*/
    else set_measurements_zero(device_ptr);
    return res;
}

/* Write the value of the sensor struct instance's one shot register to the sensor one shot register */
int8_t write_out_one_shot_register(struct PAC1720_device *device_ptr)
{
    /* Null pointer check */
    if(device_ptr->internal == NULL) return PAC1720_NULLPTR_ERROR;
    /* Write single register and return result of bus write function */
    return write_registers(device_ptr, one_shot_register_address, &device_ptr->DEV_one_shot_reg, 1);
}

/******************************* Private function definitions *****************************************/

/*!
 * @brief Set sensor to sleep mode.
 */
int8_t set_sensor_to_sleep(struct PAC1720_device *device_ptr)
{
    /* Set standby mode in configuration */
    uint8_t config_reg = CONFIG_STANDBY;
    /* Write configuration to sensor */
    return write_registers(device_ptr, configuration_register_address, &config_reg, 1);
}

/*!
 * @brief Return if sensor sleeps.
 */
bool sensor_is_in_sleep(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    /* Temporary result */
    uint8_t config_reg = 0;
    /* Read the config resgister of sensor */
    res = read_registers(device_ptr, configuration_register_address, &config_reg, 1);
    /* If communication fails or config isn't set to sleep return false*/
    if(res != PAC1720_OK || config_reg != CONFIG_STANDBY) return false;
    return true;
}

/*!
 * @brief If no name is provided by user the default name is set to the name options in sensor struct instance. 
 */
void check_name_opt(struct PAC1720_device *device_ptr)
{
    if(device_ptr->DEV_name_opt == NULL)
        device_ptr->DEV_name_opt = default_name;
    if(device_ptr->DEV_CH1_conf.CH_name_opt == NULL)
        device_ptr->DEV_CH1_conf.CH_name_opt = default_name;
    if(device_ptr->DEV_CH2_conf.CH_name_opt == NULL)
        device_ptr->DEV_CH2_conf.CH_name_opt = default_name;
}

/*!
 * @brief Writes the configuration of the sensor struct instance to the sensor. 
 */
int8_t write_all_settings_to_sensor(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    res = write_out_global_config_registers(device_ptr);
    if(res != PAC1720_OK) return res;
    res = write_out_sampling_config_registers(device_ptr);
    if(res != PAC1720_OK) return res;
    write_out_limit_registers(device_ptr);
    return res;
}

/*!
 * @brief Writes the global configuration of the sensor struct instance to the sensor. 
 */
int8_t write_out_global_config_registers(struct PAC1720_device *device_ptr)
{
    /* Temporary data for write function */
    uint8_t tmp_config_reg[4] = {0};
    /* Read config from sensor to temporary data */
    assign_tmp_global_config_array(device_ptr, tmp_config_reg);
    /* Write temporary data to sensor */
    return write_registers(device_ptr, configuration_register_address, tmp_config_reg, GLOBAL_CONFIG_REGISTERS_LENGTH);
}

/*!
 * @brief Writes global config from sensor to temporary data array. 
 */
void assign_tmp_global_config_array(struct PAC1720_device *device_ptr, uint8_t tmp_config_reg[4])
{
    tmp_config_reg[0] = device_ptr->DEV_configuration_reg;
    tmp_config_reg[1] = device_ptr->DEV_conversion_rate_reg;
    tmp_config_reg[2] = device_ptr->DEV_one_shot_reg;
    tmp_config_reg[3] = device_ptr->DEV_mask_reg;
}

/*!
 * @brief Writes the sampling settings of the sensor struct instance to the sensor. 
 */
int8_t write_out_sampling_config_registers(struct PAC1720_device *device_ptr)
{
    /* Temporary data for write function */
    uint8_t tmp_smpl_conf_reg[3] = {0};
    /* Read config from sensor to temporary data */
    assign_tmp_sampling_config_array(device_ptr, tmp_smpl_conf_reg);
    /* Write temporary data to sensor */
    return write_registers(device_ptr, v_source_sampling_configuration_register_address, tmp_smpl_conf_reg, SAMPLING_CONFIG_REGISTERS_LENGTH);
}

/*!
 * @brief Writes sampling settings from sensor channels to temporary data array. 
 */
void assign_tmp_sampling_config_array(struct PAC1720_device *device_ptr, uint8_t tmp_smpl_conf_reg[3])
{ 
    /* Values are shifted into the correct order within bytes to write them to a register*/
    tmp_smpl_conf_reg[0] |= device_ptr->DEV_CH1_conf.CH_source_voltage_sampling_time_reg        <<  SHIFT_TWO_BITS;
    tmp_smpl_conf_reg[0] |= device_ptr->DEV_CH1_conf.CH_source_voltage_sampling_average_reg;    //no shift
    
    tmp_smpl_conf_reg[1] |= device_ptr->DEV_CH1_conf.CH_current_sense_sampling_time_reg         <<  SHIFT_FOUR_BITS;
    tmp_smpl_conf_reg[1] |= device_ptr->DEV_CH1_conf.CH_current_sense_sampling_average_reg      <<  SHIFT_TWO_BITS;
    tmp_smpl_conf_reg[1] |= device_ptr->DEV_CH1_conf.CH_current_sense_FSR_reg;                  //no shift
   
    tmp_smpl_conf_reg[0] |= device_ptr->DEV_CH2_conf.CH_source_voltage_sampling_time_reg        <<  SHIFT_SIX_BITS;
    tmp_smpl_conf_reg[0] |= device_ptr->DEV_CH2_conf.CH_source_voltage_sampling_average_reg     <<  SHIFT_FOUR_BITS;

    tmp_smpl_conf_reg[2] |= device_ptr->DEV_CH2_conf.CH_current_sense_sampling_time_reg         <<  SHIFT_FOUR_BITS;
    tmp_smpl_conf_reg[2] |= device_ptr->DEV_CH2_conf.CH_current_sense_sampling_average_reg      <<  SHIFT_TWO_BITS;
    tmp_smpl_conf_reg[2] |= device_ptr->DEV_CH2_conf.CH_current_sense_FSR_reg;                  //no shift
}

/*!
 * @brief Writes the limit values of the sensor struct instance to the sensor. 
 */
int8_t write_out_limit_registers(struct PAC1720_device *device_ptr)
{
    /* Temporary data for write function */
    uint8_t tmp_lmt_reg[8] = {0};
    /* Read config from sensor to temporary data */
    assign_tmp_limit_array(device_ptr, tmp_lmt_reg);
    /* Write temporary data to sensor */
    return write_registers(device_ptr, ch1_sense_voltage_high_limit_register_address, tmp_lmt_reg, LIMIT_REGISTERS_LENGTH);
}

/*!
 * @brief Writes limit values from sensor channels to temporary data array. 
 */
void assign_tmp_limit_array(struct PAC1720_device *device_ptr, uint8_t tmp_lmt_reg[8])

{   /* Interleave array according to sensor register */
    tmp_lmt_reg[0] = device_ptr->DEV_CH1_conf.CH_current_sense_high_limit_reg;
    tmp_lmt_reg[2] = device_ptr->DEV_CH1_conf.CH_current_sense_low_limit_reg;
    tmp_lmt_reg[4] = device_ptr->DEV_CH1_conf.CH_source_voltage_high_limit_reg;
    tmp_lmt_reg[6] = device_ptr->DEV_CH1_conf.CH_source_voltage_low_limit_reg;

    tmp_lmt_reg[1] = device_ptr->DEV_CH2_conf.CH_current_sense_high_limit_reg;
    tmp_lmt_reg[3] = device_ptr->DEV_CH2_conf.CH_current_sense_low_limit_reg ;
    tmp_lmt_reg[5] = device_ptr->DEV_CH2_conf.CH_source_voltage_high_limit_reg;
    tmp_lmt_reg[7] = device_ptr->DEV_CH2_conf.CH_source_voltage_low_limit_reg;
}

/*!
 * @brief Gets all actual settings from the sensor. 
 */
int8_t get_all_settings_from_sensor(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    res = readin_global_config_registers(device_ptr);
    if(res != PAC1720_OK) return res;
    res = readin_sampling_config_registers(device_ptr);
    if(res != PAC1720_OK) return res;
    res = readin_limit_registers(device_ptr);
    if(res != PAC1720_OK) return res;
    res = readin_sensor_infos_registers(device_ptr);
    
    return res;
}

/*!
 * @brief . 
 */
int8_t readin_global_config_registers(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    uint8_t tmp_config_reg[4] = {0};
    res = read_registers(device_ptr, configuration_register_address, tmp_config_reg, GLOBAL_CONFIG_REGISTERS_LENGTH);
    assign_global_config_registers(device_ptr, tmp_config_reg);
    return res;
}

void assign_global_config_registers(struct PAC1720_device *device_ptr, uint8_t tmp_config_reg[4])
{ 
    device_ptr->DEV_configuration_reg   = tmp_config_reg[0];
    device_ptr->DEV_conversion_rate_reg = tmp_config_reg[1];
    device_ptr->DEV_one_shot_reg        = tmp_config_reg[2];
    device_ptr->DEV_mask_reg            = tmp_config_reg[3];
}

int8_t readin_limit_status_registers(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    uint8_t tmp_limit_reg[2] = {0};
    res = read_registers(device_ptr, high_limit_status_register_address, tmp_limit_reg, LIMIT_STATUS_REGISTERS_LENGTH);
    assign_limit_status_registers(device_ptr, tmp_limit_reg);
    return res;
}

void assign_limit_status_registers(struct PAC1720_device *device_ptr, uint8_t tmp_limit_reg[2])
{
    if(first_channel_is_active(device_ptr))
    {
        device_ptr->DEV_CH1_measurements.conversion_done            = (bool) (tmp_limit_reg[0] & BITMASK_CONVERSION_CMPL); 
        device_ptr->DEV_CH1_measurements.sense_voltage_high_limit   = (bool) (tmp_limit_reg[0] & BITMASK_CH1_VSENSE_LIMIT);
        device_ptr->DEV_CH1_measurements.source_voltage_high_limit  = (bool) (tmp_limit_reg[0] & BITMASK_CH1_VSRC_LIMIT);
        device_ptr->DEV_CH1_measurements.sense_voltage_low_limit    = (bool) (tmp_limit_reg[1] & BITMASK_CH1_VSENSE_LIMIT);
        device_ptr->DEV_CH1_measurements.source_voltage_low_limit   = (bool) (tmp_limit_reg[1] & BITMASK_CH1_VSRC_LIMIT);
    }
    if(second_channel_is_active(device_ptr))
    {
        device_ptr->DEV_CH2_measurements.conversion_done            = (bool) (tmp_limit_reg[0] & BITMASK_CONVERSION_CMPL); 
        device_ptr->DEV_CH2_measurements.sense_voltage_high_limit   = (bool) (tmp_limit_reg[0] & BITMASK_CH2_VSENSE_LIMIT);
        device_ptr->DEV_CH2_measurements.source_voltage_high_limit  = (bool) (tmp_limit_reg[0] & BITMASK_CH2_VSRC_LIMIT);
        device_ptr->DEV_CH2_measurements.sense_voltage_low_limit    = (bool) (tmp_limit_reg[1] & BITMASK_CH2_VSENSE_LIMIT);
        device_ptr->DEV_CH2_measurements.source_voltage_low_limit   = (bool) (tmp_limit_reg[1] & BITMASK_CH2_VSRC_LIMIT);
    }
}

int8_t readin_sampling_config_registers(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    uint8_t tmp_smpl_conf_reg[3] = {0};
    res = read_registers(device_ptr, v_source_sampling_configuration_register_address, tmp_smpl_conf_reg, SAMPLING_CONFIG_REGISTERS_LENGTH);
    assign_sampling_config_registers(device_ptr, tmp_smpl_conf_reg);
    return res;
}

void assign_sampling_config_registers(struct PAC1720_device *device_ptr, uint8_t tmp_smpl_conf_reg[3])
{ 
    device_ptr->DEV_CH1_conf.CH_source_voltage_sampling_time_reg    = (tmp_smpl_conf_reg[0] & BITMASK_THIRD_TWO)            >> SHIFT_TWO_BITS;
    device_ptr->DEV_CH1_conf.CH_source_voltage_sampling_average_reg = (tmp_smpl_conf_reg[0] & BITMASK_FOURTH_TWO);          //no shift
    device_ptr->DEV_CH1_conf.CH_current_sense_sampling_time_reg     = (tmp_smpl_conf_reg[1] & BITMASK_MSB_CURRENT_SAMPLE)   >> SHIFT_FOUR_BITS;
    device_ptr->DEV_CH1_conf.CH_current_sense_sampling_average_reg  = (tmp_smpl_conf_reg[1] & BITMASK_THIRD_TWO)            >> SHIFT_TWO_BITS;
    device_ptr->DEV_CH1_conf.CH_current_sense_FSR_reg               = (tmp_smpl_conf_reg[1] & BITMASK_FOURTH_TWO);          //no shift
   
    device_ptr->DEV_CH2_conf.CH_source_voltage_sampling_time_reg    = (tmp_smpl_conf_reg[0] & BITMASK_FIRST_TWO)            >> SHIFT_SIX_BITS;
    device_ptr->DEV_CH2_conf.CH_source_voltage_sampling_average_reg = (tmp_smpl_conf_reg[0] & BITMASK_SECOND_TWO)           >> SHIFT_FOUR_BITS;
    device_ptr->DEV_CH2_conf.CH_current_sense_sampling_time_reg     = (tmp_smpl_conf_reg[2] & BITMASK_MSB_CURRENT_SAMPLE)   >> SHIFT_FOUR_BITS;
    device_ptr->DEV_CH2_conf.CH_current_sense_sampling_average_reg  = (tmp_smpl_conf_reg[2] & BITMASK_THIRD_TWO)            >> SHIFT_TWO_BITS;
    device_ptr->DEV_CH2_conf.CH_current_sense_FSR_reg               = (tmp_smpl_conf_reg[2] & BITMASK_FOURTH_TWO);          //no shift
}

int8_t readin_measurements_registers(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    uint8_t tmp_meas_reg[12] = {0};
    res = read_registers(device_ptr, ch1_sense_voltage_high_register_address, tmp_meas_reg, READING_REGISTERS_LENGTH);
    assign_internal_measurements_registers(device_ptr, tmp_meas_reg);
    return res;
}

void assign_internal_measurements_registers(struct PAC1720_device *device_ptr, uint8_t tmp_meas_reg[12])
{
    struct PAC1720_meas_internal *meas_internal = NULL;
    if(first_channel_is_active(device_ptr))
    {
        device_ptr->DEV_CH1_measurements.meas_cnt++;
        meas_internal = device_ptr->DEV_CH1_measurements.meas_internal;
        meas_internal->v_sense_voltage_reg  = combine_bytes(&tmp_meas_reg[1], &tmp_meas_reg[0]);
        meas_internal->v_source_voltage_reg = combine_bytes(&tmp_meas_reg[5], &tmp_meas_reg[4]);
        meas_internal->power_ratio_reg      = combine_bytes(&tmp_meas_reg[9], &tmp_meas_reg[8]);
    }
    if(second_channel_is_active(device_ptr))
    {
        device_ptr->DEV_CH2_measurements.meas_cnt++;
        meas_internal = device_ptr->DEV_CH2_measurements.meas_internal;
        meas_internal->v_sense_voltage_reg  = combine_bytes(&tmp_meas_reg[3], &tmp_meas_reg[2]);
        meas_internal->v_source_voltage_reg = combine_bytes(&tmp_meas_reg[7], &tmp_meas_reg[6]);
        meas_internal->power_ratio_reg      = combine_bytes(&tmp_meas_reg[11],&tmp_meas_reg[10]);
    }
}

void set_measurements_zero(struct PAC1720_device *device_ptr)
{
    struct PAC1720_meas_internal *meas_internal = NULL;
    if(device_ptr->DEV_CH1_measurements.meas_internal != NULL)
    {
        meas_internal = device_ptr->DEV_CH1_measurements.meas_internal;
        meas_internal->v_sense_voltage_reg  = 0;
        meas_internal->v_source_voltage_reg = 0;
        meas_internal->power_ratio_reg      = 0;
    }
    if(device_ptr->DEV_CH2_measurements.meas_internal != NULL)
    {
        meas_internal = device_ptr->DEV_CH2_measurements.meas_internal;
        meas_internal->v_sense_voltage_reg  = 0;
        meas_internal->v_source_voltage_reg = 0;
        meas_internal->power_ratio_reg      = 0;
    }
    device_ptr->DEV_CH1_measurements.sense_voltage_high_limit   = device_ptr->DEV_CH2_measurements.sense_voltage_high_limit     = false;
    device_ptr->DEV_CH1_measurements.source_voltage_high_limit  = device_ptr->DEV_CH2_measurements.source_voltage_high_limit    = false;
    device_ptr->DEV_CH1_measurements.sense_voltage_low_limit    = device_ptr->DEV_CH2_measurements.sense_voltage_low_limit      = false;
    device_ptr->DEV_CH1_measurements.source_voltage_low_limit   = device_ptr->DEV_CH2_measurements.source_voltage_low_limit     = false;
    device_ptr->DEV_CH1_measurements.SOURCE_VOLTAGE             = device_ptr->DEV_CH2_measurements.SOURCE_VOLTAGE               = 0;
    device_ptr->DEV_CH1_measurements.SENSE_VOLTAGE              = device_ptr->DEV_CH2_measurements.SENSE_VOLTAGE                = 0;
    device_ptr->DEV_CH1_measurements.CURRENT                    = device_ptr->DEV_CH2_measurements.CURRENT                      = 0;
    device_ptr->DEV_CH1_measurements.POWER                      = device_ptr->DEV_CH2_measurements.POWER                        = 0;
} 

int8_t readin_limit_registers(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    uint8_t tmp_lmt_reg[8] = {0};
    res = read_registers(device_ptr, ch1_sense_voltage_high_limit_register_address, tmp_lmt_reg, LIMIT_REGISTERS_LENGTH);
    assign_ch_limit_registers(device_ptr, tmp_lmt_reg);
    return res;
}

void assign_ch_limit_registers(struct PAC1720_device *device_ptr, uint8_t tmp_lmt_reg[8])
{
    device_ptr->DEV_CH1_conf.CH_current_sense_high_limit_reg = tmp_lmt_reg[0];
    device_ptr->DEV_CH1_conf.CH_current_sense_low_limit_reg = tmp_lmt_reg[2];
    device_ptr->DEV_CH1_conf.CH_source_voltage_high_limit_reg = tmp_lmt_reg[4];
    device_ptr->DEV_CH1_conf.CH_source_voltage_low_limit_reg = tmp_lmt_reg[6];

    device_ptr->DEV_CH2_conf.CH_current_sense_high_limit_reg = tmp_lmt_reg[1];
    device_ptr->DEV_CH2_conf.CH_current_sense_low_limit_reg = tmp_lmt_reg[3];
    device_ptr->DEV_CH2_conf.CH_source_voltage_high_limit_reg = tmp_lmt_reg[5];
    device_ptr->DEV_CH2_conf.CH_source_voltage_low_limit_reg = tmp_lmt_reg[7];
}

int8_t readin_sensor_infos_registers(struct PAC1720_device *device_ptr)
{
    uint8_t res = PAC1720_OK;
    if(device_ptr->internal == NULL) return PAC1720_NULLPTR_ERROR;
    uint8_t tmp_read[3] = {0};
    res = read_registers(device_ptr, product_id_register_address, tmp_read, SENSOR_INFO_REGISTER_LENGHT);
    struct PAC1720_internal *internal = device_ptr->internal;
    assign_sensor_infos_registers(internal, tmp_read);
    return res;
}

void assign_sensor_infos_registers(struct PAC1720_internal *internal, uint8_t tmp_read[3])
{
    internal->sensor_product_id     = tmp_read[0];
    internal->sensor_manufact_id    = tmp_read[1];
    internal->sensor_revision       = tmp_read[2];
}

int8_t create_all_internal_ptrs(struct PAC1720_device *device_ptr, const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay)
{
        device_ptr->internal = create_internal_ptr(ext_write, ext_read, ext_delay);
        if( device_ptr->internal == NULL ) 
        {
            return PAC1720_INIT_ERROR;
        }
        device_ptr->DEV_CH1_conf.ch_internal = create_ch_internal_ptr();
        device_ptr->DEV_CH1_measurements.meas_internal = create_meas_internal_ptr();
        if ( device_ptr->DEV_CH1_conf.ch_internal == NULL || device_ptr->DEV_CH1_measurements.meas_internal == NULL ) 
        {
            return PAC1720_INIT_ERROR;
        }
        device_ptr->DEV_CH2_conf.ch_internal = create_ch_internal_ptr();
        device_ptr->DEV_CH2_measurements.meas_internal = create_meas_internal_ptr();
        if ( device_ptr->DEV_CH2_conf.ch_internal == NULL || device_ptr->DEV_CH2_measurements.meas_internal == NULL ) 
        {
            return PAC1720_INIT_ERROR;
        }
        return PAC1720_OK;
}

struct PAC1720_internal * create_internal_ptr(const PAC1720_fptr ext_write, const PAC1720_fptr ext_read, const delay_fptr ext_delay) 
{
    struct PAC1720_internal * internal = (struct PAC1720_internal *) calloc(1, sizeof(struct PAC1720_internal));
    if(internal == NULL) return internal;
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
        dev_ptr->DEV_CH1_measurements.meas_internal = NULL;
    }
    if(dev_ptr->DEV_CH2_measurements.meas_internal != NULL){
        destroy_meas_internal_ptr(dev_ptr->DEV_CH2_measurements.meas_internal);
        dev_ptr->DEV_CH2_measurements.meas_internal = NULL;
    }
    if(dev_ptr->DEV_CH1_conf.ch_internal != NULL){
        destroy_ch_internal_ptr(dev_ptr->DEV_CH1_conf.ch_internal);
        dev_ptr->DEV_CH1_conf.ch_internal = NULL;
    }
    if(dev_ptr->DEV_CH2_conf.ch_internal != NULL){
        destroy_ch_internal_ptr(dev_ptr->DEV_CH2_conf.ch_internal);
        dev_ptr->DEV_CH2_conf.ch_internal = NULL;
    }
    if(dev_ptr->internal != NULL){
        destroy_internal_ptr(dev_ptr->internal);
        dev_ptr->internal = NULL;
    } 
}

void destroy_internal_ptr(struct PAC1720_internal *internal)
{
    if(sizeof(*internal) == sizeof(struct PAC1720_internal))
    {
        internal->read               = NULL;
        internal->write              = NULL;
        internal->delay_ms           = NULL;
        internal->sensor_product_id  = 0;
        internal->sensor_manufact_id = 0;
        internal->sensor_revision    = 0;
    }
    free(internal);
}

void destroy_ch_internal_ptr(struct PAC1720_ch_internal *ch_internal)
{   
    if(sizeof(*ch_internal) == sizeof(struct PAC1720_ch_internal))
    {
        ch_internal->current_sense_FSC  = 0;
        ch_internal->source_voltage_FSV = 0;
        ch_internal->power_sense_FSP    = 0;
    }
    free(ch_internal);
}

void destroy_meas_internal_ptr(struct PAC1720_meas_internal *meas_internal)
{ 
    if(sizeof(*meas_internal) == sizeof(struct PAC1720_meas_internal))
    {
        meas_internal->v_source_voltage_reg = 0;
        meas_internal->v_sense_voltage_reg  = 0;
        meas_internal->power_ratio_reg      = 0;
    }
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

int8_t calculate_all_measurements(struct PAC1720_device *device_ptr)
{
    int8_t res = PAC1720_OK;
    if (first_channel_is_active(device_ptr))
    {
        res = calculate_channel_measurements(&device_ptr->DEV_CH1_conf, &device_ptr->DEV_CH1_measurements);
        if(res != PAC1720_OK) return res;
    } 
    if (second_channel_is_active(device_ptr))
    { 
        res = calculate_channel_measurements(&device_ptr->DEV_CH2_conf, &device_ptr->DEV_CH2_measurements);
    } 
    return res;
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
    res = set_channel_FSx_coefficients(&device_ptr->DEV_CH1_conf);
    if (res != PAC1720_OK) return res;
    res = set_channel_FSx_coefficients(&device_ptr->DEV_CH2_conf);
    return res;
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

int8_t calculate_BUS_CURRENT(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements)
{   
    struct PAC1720_ch_internal   *  internal_config      = channel_conf->ch_internal;
    struct PAC1720_meas_internal *  internal_measurement = channel_measurements->meas_internal;
    if(internal_config->current_sense_FSC != 0){

        float FSC = internal_config->current_sense_FSC;
        float Vsense= calculate_SENSED_VOLTAGE(&internal_measurement->v_sense_voltage_reg, &channel_conf->CH_current_sense_sampling_time_reg);
        float DENOMINATOR = DENOMINATOR_values_current_sense[channel_conf->CH_current_sense_sampling_time_reg];
        float Ibus_current = FSC * (Vsense / DENOMINATOR);

        channel_measurements->SENSE_VOLTAGE = Ibus_current * channel_conf->CH_current_sense_resistor_value;
        channel_measurements->CURRENT = Ibus_current;
        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}
 
int8_t calculate_BUS_VOLTAGE(const struct PAC1720_CH_config *channel_conf, struct PAC1720_CH_measurements *channel_measurements)
{
    struct PAC1720_ch_internal   *  internal_config      = channel_conf->ch_internal;
    struct PAC1720_meas_internal *  internal_measurement = channel_measurements->meas_internal;
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
    struct PAC1720_ch_internal   * internal_config  = channel_conf->ch_internal;
    struct PAC1720_meas_internal * internal_meas    = channel_measurements->meas_internal;

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
    if( config_ptr != NULL && config_ptr->ch_internal != NULL && config_ptr->CH_current_sense_resistor_value != 0 ){
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
    if( config_ptr != NULL && config_ptr->ch_internal != NULL ){
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
    if( ch_internal_ptr != NULL && ch_internal_ptr->current_sense_FSC != 0 && ch_internal_ptr->source_voltage_FSV != 0 ){

        ch_internal_ptr->power_sense_FSP = ch_internal_ptr->current_sense_FSC * ch_internal_ptr->source_voltage_FSV;

        return PAC1720_OK;
    } else {
        return PAC1720_FAILURE;
    }
}

uint8_t get_sensor_product_id(struct PAC1720_device *device_ptr)
{
    if(device_ptr->internal != NULL){
        struct PAC1720_internal * internal = device_ptr->internal;
        if(internal->sensor_product_id != 0){
            return internal->sensor_product_id;
        }
    }
    return PAC1720_UNSIGNED_ERROR;
}

uint8_t get_sensor_manufact_id(struct PAC1720_device *device_ptr)
{
    if(device_ptr->internal != NULL){
        struct PAC1720_internal * internal = device_ptr->internal;
        if(internal->sensor_manufact_id != 0){
            return internal->sensor_manufact_id;
        }
    }
    return PAC1720_UNSIGNED_ERROR;
}

uint8_t get_sensor_revision_id(struct PAC1720_device *device_ptr)
{
    if(device_ptr->internal != NULL){
        struct PAC1720_internal * internal = device_ptr->internal;
        if(internal->sensor_revision != 0){
            return internal->sensor_revision;
        }
    }
    return PAC1720_UNSIGNED_ERROR;
}

float get_channel_FSC(struct PAC1720_CH_config *config_ptr)
{
    if(config_ptr->ch_internal != NULL){
        struct PAC1720_ch_internal * internal = config_ptr->ch_internal;
        if(internal->current_sense_FSC != 0){
            return internal->current_sense_FSC;
        }
    }
    return (float) PAC1720_FAILURE;
}

float get_channel_FSV(struct PAC1720_CH_config *config_ptr)
{
    if(config_ptr->ch_internal != NULL){
        struct PAC1720_ch_internal * internal = config_ptr->ch_internal;
        if(internal->source_voltage_FSV != 0){
            return internal->source_voltage_FSV;
        }
    }
    return (float) PAC1720_FAILURE;
}

float get_channel_FSP(struct PAC1720_CH_config *config_ptr)
{
    if(config_ptr->ch_internal != NULL){
        struct PAC1720_ch_internal * internal = config_ptr->ch_internal;
        if(internal->power_sense_FSP != 0){
            return internal->power_sense_FSP;
        }
    }
    return (float) PAC1720_FAILURE;
}

uint16_t get_channel_src_voltage_read(struct PAC1720_CH_measurements *meas_ptr)
{
    if(meas_ptr->meas_internal != NULL){
        struct PAC1720_meas_internal * internal = meas_ptr->meas_internal;
        return internal->v_source_voltage_reg;
    }
    return (uint16_t) (PAC1720_UNSIGNED_ERROR << SHIFT_IN_BYTES_OFFSET) | PAC1720_UNSIGNED_ERROR;
}

uint16_t get_channel_sense_voltage_read(struct PAC1720_CH_measurements *meas_ptr)
{
    if(meas_ptr->meas_internal != NULL){
        struct PAC1720_meas_internal * internal = meas_ptr->meas_internal;
        return internal->v_sense_voltage_reg;
    }
    return (uint16_t) (PAC1720_UNSIGNED_ERROR << SHIFT_IN_BYTES_OFFSET) | PAC1720_UNSIGNED_ERROR;
}

uint16_t get_channel_pwr_ratio_read(struct PAC1720_CH_measurements *meas_ptr) 
{
    if(meas_ptr->meas_internal != NULL){
        struct PAC1720_meas_internal * internal = meas_ptr->meas_internal;
        return internal->power_ratio_reg;
    }
    return (uint16_t) (PAC1720_UNSIGNED_ERROR << SHIFT_IN_BYTES_OFFSET) | PAC1720_UNSIGNED_ERROR;
}

uint16_t combine_bytes(const uint8_t *lsb, const uint8_t *msb)
{
    return (*msb << SHIFT_IN_BYTES_OFFSET) + *lsb;
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

bool first_channel_is_active(const struct PAC1720_device *device_ptr)
{
    uint8_t ch1_disable_bits = device_ptr->DEV_configuration_reg & BITMASK_CH1_DISABLED;

    return ( ch1_disable_bits != BITMASK_CH1_DISABLED && device_ptr->DEV_CH1_conf.ch_internal != NULL 
             && device_ptr->DEV_CH1_measurements.meas_internal != NULL );
}

bool second_channel_is_active(const struct PAC1720_device *device_ptr)
{
    uint8_t ch2_disable_bits    = device_ptr->DEV_configuration_reg & BITMASK_CH2_DISABLED;

    return ( ch2_disable_bits != BITMASK_CH2_DISABLED && device_ptr->DEV_CH2_conf.ch_internal != NULL 
             && device_ptr->DEV_CH2_measurements.meas_internal != NULL );
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
                                                 (void*) &assign_ch_limit_registers,//////////
                                                 (void*) &assign_internal_measurements_registers,/////////
                                                 (void*) &combine_bytes,
                                                 (void*) &assign_sampling_config_registers,//////////
                                                 (void*) &assign_limit_status_registers,///////////
                                                 (void*) &create_internal_ptr,
                                                 (void*) &create_ch_internal_ptr,
                                                 (void*) &destroy_internal_ptr,
                                                 (void*) &destroy_ch_internal_ptr,
                                                 (void*) &peripherals_null_pointer_check,
                                                 (void*) &create_meas_internal_ptr,
                                                 (void*) &destroy_meas_internal_ptr,
                                                 (void*) &set_measurements_zero,/////////////////
                                                 (void*) &assign_tmp_sampling_config_array,////////
                                                 (void*) &assign_tmp_limit_array////////////
                                            };
    return &test_fptr_field;
}
