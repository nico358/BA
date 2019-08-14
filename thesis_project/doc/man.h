/** @mainpage Current Monitor API
 *  
 *  This API provides access to the PAC1720 current sensors. It allows configuration and query functionality on the sensors.
 *  The main interface is the struct PAC1720_device. An instance of the struct must be provided to the init function of the API
 *  in order to configure the sensor. Two ways for initialization are possible. 
 * 
 *  *  @section sec1 Initialization with settings from sensor 
 * 
 *  The first way for an initialization is a call of the function adapter_init_PAC1720_from_field. Here, the configuration stored in the struct instance 
 *  is overwritten by the settings on the sensor. The values DEV_name_opt, CH_name_opt, DEV_sensor_address, CH_current_sense_resistor_value remain untouched. 
 *  This is the simplest way to initialize the driver module since all settings are captured from the sensor and only three mandatory settings are rqeuired as shown below:
 * 
 * // Absolute minimum settings required for an initialization:
 * struct PAC1720_device dev_FPGA_VCC = 
 * {
 * 	   .DEV_sensor_address                                     = 0x4F,
 *     .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
 *     .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
 * };
 *
 * 
 *  *  @section sec2 Initialization with settings from struct instance
 *  
 * The second possibility to initialize the driver module is to provide the struct instance at a call of the function adapter_init_PAC1720_user_defined.
 * This function takes the configuration that is stored in the struct and initializes the sensor with it. Basically can the configuration be made with default
 * values which are almost equal to zero within this context. To achive this, the struct is to be initialized accordingly. The setting of some values has to be 
 * different from zero to make the configuration default. The minimum required setting for this way of initialization is depicted in the minimum example. 
 * If the configuration of the sensor is to be further adjusted, all other settings can be made in the corresponding instance. The full configuration is shown in
 * the large example. Note that all values are just samples and may be changed to your own needs.
 * 
 * // Minimum settings required for an initialization:
 * struct PAC1720_device dev_FPGA_VCC = 
 * {
 *     .DEV_sensor_address                                     = 0x4F,
 *     .DEV_conversion_rate_reg                                = CONVERSION_DEFAULT,
 *     .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
 *     .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_DEFAULT,
 *     .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_DEFAULT,
 *     .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_DEFAULT,
 *
 *     .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
 *     .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_DEFAULT,
 *     .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_DEFAULT,
 *     .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_DEFAULT,
 * }; 
 *
 * 
 * // All possible configuration settings:
 *struct PAC1720_device dev_USB_MON = 
 *{
 *	 .DEV_name_opt                                           = "device_identifier",
 *	 .DEV_sensor_address                                     = 0x4D,
 *   .DEV_configuration_reg                                  = CONFIG_ALL_CH_ENABLED,
 *	 .DEV_conversion_rate_reg                                = CONVERSION_CONTINIOUS,
 *	 .DEV_one_shot_reg                                       = ONE_SHOT_DEFAULT,
 *   .DEV_mask_reg                                           = MASK_ALL_CH_ALERT_ASSERT,
 *
 *   .DEV_CH1_conf.CH_name_opt                               = "channel1_identifier",
 *   .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.15f,
 *   .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
 *   .DEV_CH1_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
 *   .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
 *   .DEV_CH1_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
 *   .DEV_CH1_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
 *   .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
 *   .DEV_CH1_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
 *   .DEV_CH1_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
 *	 .DEV_CH1_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
 *
 *   .DEV_CH2_conf.CH_name_opt                               = "channel2_identifier",
 *   .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
 *   .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_2ms5,
 *   .DEV_CH2_conf.CH_current_sense_sampling_average_reg     = SAMPLE_AVERAGING_DISABLED,
 *   .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_20mV,
 *   .DEV_CH2_conf.CH_current_sense_high_limit_reg           = CURRENT_SENSE_HIGH_LIMIT_DEFAULT,
 *	 .DEV_CH2_conf.CH_current_sense_low_limit_reg            = CURRENT_SENSE_LOW_LIMIT_DEFAULT,
 *   .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_2ms5,
 *   .DEV_CH2_conf.CH_source_voltage_sampling_average_reg    = SAMPLE_AVERAGING_DISABLED,
 *   .DEV_CH2_conf.CH_source_voltage_high_limit_reg          = SOURCE_VOLTAGE_HIGH_LIMIT_DEFAULT,
 *	 .DEV_CH2_conf.CH_source_voltage_low_limit_reg           = SOURCE_VOLTAGE_LOW_LIMIT_DEFAULT,
 *};
 * 
 *  @section sec2 Driver 
 *
 */