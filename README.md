# Current Measurement Library
The Current Measurement Library provides an API for configuration and query of the PAC1720 current sensors. Multiple sensors can be controlled by means of the library. It is designed to be portable an can be adapted to an individual application by the adapter module. 

## Introduction
The driver module of the library contains its core functionality such as calculation of the sensor values. The adapter serves as wrapper for the driver and can be changed to the user's need in order to fit the library to an application. A generic communication interface is provided by the adapter module that allows the driver to communicate with the sensors by a serial bus such as the TWI. Therefore an implementation of the bus communication interface is to be provided to the adapter. After initialization of the adapter module the measurements can be triggered and the results read from the relevant interface.

## Dependencies

Dependencies of the Current Measurement API used at its development:

+ bazel 0.24.0
+ EmbeddedSystemsBuildScripts 0.4.6
+ i2cmaster library
+ LUFA

[Source Repo for some dependencies](http://artifactory.es.uni-due.de:8081/artifactory/libs-release-local/FKS/embedded-systems-build-scripts/0.4.6/embedded-systems-build-scripts.tar.gz)


## Documentation

### Code Documentation

The code has been documented using Doxygen. Open the file index.html in folder doc/html to get an overview about the project.

## Required configuration

A `WORKSPACE` file in the project folder is required to setup the bazel toolchain. Follow the manual on `https://github.com/es-ude/EmbeddedSystemsBuildScripts`. In the `BUILD` file add your application source file to a default embedded build rule and add a `cc_library` containing the Current Measurement Library to the dependencies. When building the project the dependencies are automatically managed.

## How to flash

The flashing was done with the 'avr dude' program. Therefore the CDC bootloader of the LUFA project was flashed onto the MCU.  The bootloader uses the AVR109 programmer. To flash the application onto the MCU excute the command `sudo avrdude -c AVR109 -p <mcu> -P <port> -U flash:w:<file>.hex` in the console.

## How to use the API

### Including it

Include the header file of the adapter into your project at the desired location and modify the include of
the driver header according to the location.

```c
#include <adapter_PAC1720.h>
```

## Driver

The entry point of the sensor API is the function `adapter_init_PAC1720_user_defined`. It takes a reference to an instance of the `struct PAC1720_device` where the configuration of the sensor is stored. The sensor is initialized by the function call and the measurements can be triggered by a call to the function  `get_all_measurements_PAC1720`. Afterwards the measurements can be read from the device struct.

## Adapter

The adapter needs to be initialized before it can be used. Provide an instance of the `struct BUS_INTERFACE` to the function `adapter_init_peripherals`. This initializes the required communication interface of the adapter. The instance of the struct must be assigned to references the bus communication's implementation. Basically the adapter wraps the driver API and provides an interface to it. The function `adapter_init_PAC1720_user_defined` is to be called with an `struct PAC1720_device` instance as described above. Internally the function `adapter_init_PAC1720_user_defined`is called. The measurements can be triggered by the function `adapter_get_measurements_PAC1720` and the reading of the results is the same as described above.

## Initialization process

Instanciate a `struct BUS_INTERFACE` and assign the addresses of the bus communication functions to the struct members. 
```c
/* Instantiate a bus interface */
struct BUS_INTERFACE external_bus_interface = {
    /** Assign i2cmaster library function pointer to members */
    .init       = &i2c_init,
    .stop       = &i2c_stop,
    .start      = &i2c_start,
    .repStart   = &i2c_rep_start,
    .startWait  = &i2c_start_wait,
    .write      = &i2c_write,
    .readAck    = &i2c_readAck,
    .readNak    = &i2c_readNak
};
```

Assign a reference to an implementation of a delay function to an instance of the relevant function pointer type.
```c
/** Assign user provided delay function to pointer */
delay_function_ptr external_delay_function = &user_delay_ms;
```

Call the init function of the adapter.
```c
 adapter_init_peripherals(&external_bus_interface, external_delay_function);
```

Instanciate a `struct PAC1720_device` and set the desired configuration. The names are optional but the resistor values of the measurement resistors are mandatory. The sensor's bus address is mandatory as well. All other settings are optional but some of them should be set to default as shown below.

```c
  // Minimum settings required for an initialization:
  struct PAC1720_device dev = 
  {
      .DEV_sensor_address                                     = 0x4F,
      .DEV_conversion_rate_reg                                = CONVERSION_DEFAULT,
      .DEV_CH1_conf.CH_current_sense_resistor_value           = 0.8f,
      .DEV_CH1_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_DEFAULT,
      .DEV_CH1_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_DEFAULT,
      .DEV_CH1_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_DEFAULT,
 
      .DEV_CH2_conf.CH_current_sense_resistor_value           = 0.8f,
      .DEV_CH2_conf.CH_current_sense_sampling_time_reg        = CURRENT_SAMPLE_TIME_DEFAULT,
      .DEV_CH2_conf.CH_current_sense_FSR_reg                  = CURRENT_SENSE_RANGE_DEFAULT,
      .DEV_CH2_conf.CH_source_voltage_sampling_time_reg       = VSRC_SAMPLE_TIME_DEFAULT,
  }; 
```


After creating an instance call the init function with a reference to the struct.
```c
adapter_init_PAC1720_from_field(&dev);
```

## Measurements

Now the measurements can be triggered by the relevant function call anproviding a reference to the device struct instance.
```c
adapter_get_measurements_PAC1720(&dev);
```

The results can be read from the measurement struct in the device instance.
```c
char *name = dev->DEV_CH1_conf.CH_name_opt, 
float current = dev->DEV_CH1_measurements.CURRENT, 
float voltage = dev->DEV_CH1_measurements.SOURCE_VOLTAGE, 
float power = dev->DEV_CH1_measurements.POWER,
```

## Deconstruction

The struct instance is to be deconstructed when not longer required.
```c
adapter_destroy_PAC1720(&dev); 
```

## Running Unit tests

The tests can be run automatically by bazel. Therefore execute the command `bazel test test:all` in the console.

# Contact

nicolas.frick@stud.uni-due.de

