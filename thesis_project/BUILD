load(
    "@AvrToolchain//:helpers.bzl",
    "cpu_frequency_flag",
    "default_embedded_binary",
    "generate_hex",
    "mcu_avr_gcc_flag",
)

commonCopts = mcu_avr_gcc_flag() + cpu_frequency_flag()

LUFA_COPTS = [
    "-Iexternal/LUFA/Demos/Device/ClassDriver/VirtualSerial/Config",
    "-isystem external/LUFA/",
]

filegroup(
	name = "LufaSetupSrcs",
	srcs = glob(["lib/LUFA-Setup/*.c"])
)

filegroup(
	name = "LufaSetupHeaders",
	srcs = glob(["lib/LUFA-Setup/*.h"])
)

exports_files(
	glob([
		"lib/circular_buffer/circular_buffer.c",
		"lib/circular_buffer/circular_buffer.h",
		"lib/current_sense/**/*.c",
		"lib/current_sense/**/*.h",
		"lib/debug/debugUsb.c",
		"lib/debug/debug.h",
		"lib/gpio/**/*.c",
		"lib/gpio/**/*.h",
		"lib/i2cmaster/twimaster.c",
		"lib/i2cmaster/i2cmaster.h",
		"lib/sensor-adapter/sensor_adapter.c",
		"lib/sensor-adapter/sensor_adapter.h",
		"lib/softSerial/**/*.c",
		"lib/softSerial/**/*.h",
		"lib/softSerial/usb/**/*.c",
		"lib/softSerial/usb/**/*.h",
	]),

	visibility = ["//test:__pkg__"],
)

cc_library(
	name = "DebugLib",
	srcs = ["lib/debug/debugUsb.c", "LufaSetupSrcs"],
	hdrs = ["lib/debug/debug.h", "LufaSetupHeaders"],

	copts = commonCopts + LUFA_COPTS,

	linkstatic = True,
	deps = ["@LUFA//:VirtualSerial"],
	visibility = ["//test:__pkg__"],
)

cc_library(
	name = "CircularBufferLib",
	srcs = glob(["lib/circular_buffer/*.c"]),
	hdrs = glob(["lib/circular_buffer/*.h"]),

	copts = commonCopts,

    deps = [":DebugLib"],
	visibility = ["//test:__pkg__"],
)

cc_library(
	name = "I2cLib",
	srcs = glob(["lib/i2cmaster/*.c"]),
	hdrs = glob(["lib/i2cmaster/*.h"]),

	copts = commonCopts,

	visibility = ["//test:__pkg__"],
)

cc_library(
	name = "CurrentMeasurementLib",
	srcs = ["lib/current_sense/current_measurement.c"],
	hdrs = ["lib/current_sense/current_measurement.h"],

	copts = commonCopts,

    deps = [
		":CircularBufferLib",
	],
	visibility = ["//test:__pkg__"],
)

cc_library(
	name = "CurrentSenseLib",
	srcs = ["lib/current_sense/current_sense.c"],
	hdrs = ["lib/current_sense/current_sense.h"],

	copts = commonCopts,

	deps = [
	 ":CircularBufferLib", 
	 ":I2cLib",
	 ":CurrentMeasurementLib", 
	 ":DebugLib",
	],
	visibility = ["//test:__pkg__"],
)

cc_library(
	name = "SensorAdapterLib",
	srcs = ["lib/sensor-adapter/sensor_adapter.c"],
	hdrs = ["lib/sensor-adapter/sensor_adapter.h"],

	copts = commonCopts,

	deps = [
	 ":CircularBufferLib", 
	 ":I2cLib", 
	 ":CurrentMeasurementLib", 
	 ":DebugLib",
	],
	visibility = ["//test:__pkg__"],
)

cc_library(
    name = "IncludeLib",
    hdrs = [
        "include/currentSenseApp.h",
    ],

    copts = commonCopts,

    deps = [
        ":DebugLib",
        ":CurrentSenseLib",
        ":CircularBufferLib",
        ":CurrentMeasurementLib",
        ":SensorAdapterLib",
        ":I2cLib"
    ],
	visibility = ["//test:__pkg__"],
)

default_embedded_binary(
	name = "Main",
	srcs = [
		"src/main.c"],

	copts = commonCopts + LUFA_COPTS,

	linkopts = commonCopts + LUFA_COPTS + ["-Wl,-u,vfprintf -lprintf_flt -lm"],

	deps = [
		":DebugLib",
        ":CurrentSenseLib",
	],
)

default_embedded_binary(
	name = "CurrentSenseApp",
	srcs = [
		"src/currentSenseApp.c",
    ],

	copts = commonCopts + LUFA_COPTS,

	linkopts = commonCopts + LUFA_COPTS + ["-Wl,-u,vfprintf -lprintf_flt -lm"],

	deps = [
		":DebugLib",
        ":CurrentSenseLib",
        ":CircularBufferLib",
        ":CurrentMeasurementLib",
        ":SensorAdapterLib",
        ":I2cLib",
        ":IncludeLib"
	],
)

