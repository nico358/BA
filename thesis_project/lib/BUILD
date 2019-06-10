package(default_visibility = ["//visibility:public"])

load(
    "@AvrToolchain//:helpers.bzl",
    "cpu_frequency_flag",
    "mcu_avr_gcc_flag",
)

commonCopts = mcu_avr_gcc_flag() + cpu_frequency_flag() # + [folderOpts]

LUFA_COPTS = [
    "-Iexternal/LUFA/Demos/Device/ClassDriver/VirtualSerial/Config",
    "-isystem external/LUFA/",
]

filegroup(
	name = "LufaSetupSrcs",
	srcs = glob(["LUFA-Setup/*.c"])
)

filegroup(
	name = "LufaSetupHeaders",
	srcs = glob(["LUFA-Setup/*.h"])
)

# lib definitions
cc_library(
	name = "DebugLib",
	srcs = ["debug/debugUsb.c", "LufaSetupSrcs"],
	hdrs = ["debug/debug.h", "LufaSetupHeaders"],

	copts = commonCopts + LUFA_COPTS,
	deps = ["@LUFA//:VirtualSerial"],
)

cc_library(
	name = "CircularBufferLib",
	srcs = glob(["circular_buffer/*.c"]),
	hdrs = glob(["circular_buffer/*.h"]),

	copts = commonCopts,
    deps = ["DebugLib"]

)

cc_library(
	name = "I2cLib",
	srcs = glob(["i2cmaster/*.c"]),
	hdrs = glob(["i2cmaster/*.h"]),

	copts = commonCopts,
)

cc_library(
	name = "CurrentMeasurementLib",
	srcs = ["current_sense/current_measurement.c"],
	hdrs = ["current_sense/current_measurement.h"],

	copts = commonCopts,
    deps = [
		"CircularBufferLib",
	]

)

cc_library(
	name = "CurrentSenseLib",
	srcs = ["current_sense/current_sense.c"],
	hdrs = ["current_sense/current_sense.h"],

	copts = commonCopts,

	deps = [
	 "CircularBufferLib", "I2cLib","CurrentMeasurementLib", "DebugLib"
	     ]
)
