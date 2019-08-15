/** @mainpage Current Monitor API
 *  
 *  This API enables configuration and data query on the PAC1720 current sensors.
 *  The main interface is the struct PAC1720_device. An instance of the struct must be provided to the init function of the API
 *  in order to configure the sensor. Once, the configuration settings are done the adapter module of the library needs to be 
 *  initialized by the relavant function to enable bus communication. After initialization the measurements can be triggered and
 *  its results queried to get the actual measurement values. The actual current consumption, source voltage and power consumption 
 *  of the measured device are available. 
 * 
 *  
 *  @section sec1 Driver initialization with settings from sensor 
 * 
 *  The simple way for an initialization is a call of the function adapter_init_PAC1720_from_field. Here, the configuration stored in the struct instance 
 *  is overwritten by the settings on the sensor. The values DEV_name_opt, CH_name_opt, DEV_sensor_address, CH_current_sense_resistor_value remain untouched. 
 *  This is the simplest way to initialize the driver module since all settings are captured from the sensor and only three mandatory settings are rqeuired as shown below:
 * 
 * @code
 * // Absolute minimum settings required for an initialization:
 * struct PAC1720_device dev = 
 * {
 *      .DEV_sensor_address                                     = 0x4F,
 *      .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
 *      .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
 * };
 *
 * @endcode
 * 
 * 
 * *  @section sec2 Driver initialization with settings from struct instance
 *  
 * The second possibility to initialize the driver module is to provide the struct instance at a call of the function adapter_init_PAC1720_user_defined.
 * This function takes the configuration that is stored in the struct and initializes the sensor with it. Basically can the configuration be made with default
 * values which are almost equal to zero within this context. To achive this, the struct is to be initialized accordingly. The setting of some values has to be 
 * different from zero to make the configuration default. The minimum required setting for this way of initialization is depicted in the minimum example. 
 * If the configuration of the sensor is to be further adjusted, all other settings can be made in the corresponding instance. The full configuration is shown in
 * the large example. Note that all values are just samples and must be changed to your own needs.
 * 
 * @code
 * // Minimum settings required for an initialization:
 * struct PAC1720_device dev = 
 * {
 *  .DEV_sensor_address                                     = 0x4F,
 *  .DEV_conversion_rate_reg                                = CONVERSION_DEFAULT,
 *  .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
 *  .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_DEFAULT,
 *  .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_DEFAULT,
 *  .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_DEFAULT,
 *
 *  .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
 *  .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_DEFAULT,
 *  .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_DEFAULT,
 *  .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_DEFAULT,
 * }; 
 *
 * 
 * // All possible configuration settings:
 *struct PAC1720_device dev = 
 *{
 *  .DEV_name_opt                                           = "device_identifier",
 *  .DEV_sensor_address                                     = 0x4D,
 *  .DEV_configuration_reg                                  = CONFIG_ALL_CH_ENABLED,
 *  .DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
 *  .DEV_one_shot_reg                                       = ONE_SHOT_DEFAULT,
 *  .DEV_mask_reg                                           = MASK_ALL_CH_ALERT_ASSERT,
 *
 *  .DEV_CH1_conf.CH_name_opt                               = "channel1_identifier",
 *  .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.15f,
 *  .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
 *  .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
 *  .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
 *  .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
 *  .DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
 *  .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
 *  .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
 *  .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
    .DEV_CH1_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
 *
 *  .DEV_CH2_conf.CH_name_opt                               = "channel2_identifier",
 *  .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
 *  .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
 *  .DEV_CH2_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
 *  .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
 *  .DEV_CH2_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
 *	.DEV_CH2_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
 *  .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
 *  .DEV_CH2_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
 *  .DEV_CH2_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
 *  .DEV_CH2_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
 *};
 * 
 * @endcode
 * 
 * 
 *  @section sec3 Initialization process
 * 
 * The adapter module connects the driver to your application. In order to enable the required bus communication via TWI (or similar) create an instance
 * of the struct BUS_INTERFACE and assign its members to the addresses of the bus interface functions. A reference to an implementation of a 
 * delay function is also required. Call the function adapter_init_peripherals with the references as parameters in order to initialize the adapter.
 * 
 * @code
 * // Instantiate a bus interface 
 * struct BUS_INTERFACE external_bus_interface = {
 *    // Assign i2cmaster library function addresses to members 
 *    .init       = &i2c_init,
 *    .stop       = &i2c_stop,
 *    .start      = &i2c_start,
 *    .repStart   = &i2c_rep_start,
 *    .startWait  = &i2c_start_wait,
 *    .write      = &i2c_write,
 *    .readAck    = &i2c_readAck,
 *    .readNak    = &i2c_readNak
 *};
 *
 * // Assign user provided delay function to pointer 
 * delay_function_ptr external_delay_function = &user_delay_ms;
 * 
 * // Initialize the adapter
 * adapter_init_peripherals(&external_bus_interface, external_delay_function);
 * @endcode
 * 
 * Now the adapter is ready to connect the driver to the application. Call the initialization function for the sensors with a reference to the
 * device struct which was instantiated according to one of the examples.
 * 
 * @code
 * adapter_init_PAC1720_user_defined(&dev);
 * @endcode
 *
 * The return value of the function tells whether the init has succeeded or failed. 
 * 
 *  @section sec4 Take measurements
 * 
 * When the sensors was initialized successfully the measurements can be triggered by calling the function adapter_get_measurements_PAC1720 
 * and afterwards the results can be read from the device struct. The function needs to be called with a reference to the device struct.
 * 
 * @code
 * // Trigger the measurement
 * adapter_get_measurements_PAC1720(&dev)
 * 
 * // Fetch results
 * char *name = dev->DEV_CH1_conf.CH_name_opt; 
 * float current = dev->DEV_CH1_measurements.CURRENT; 
 * float voltage = dev->DEV_CH1_measurements.SOURCE_VOLTAGE; 
 * float power = dev->DEV_CH1_measurements.POWER;
 * 
 * 
 * @endcode
 */