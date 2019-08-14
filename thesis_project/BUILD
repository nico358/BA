### Loading build tools ###
load(
    "@AvrToolchain//:helpers.bzl",
    "cpu_frequency_flag",
    "default_embedded_binary",
    "generate_hex",
    "mcu_avr_gcc_flag",
)

### Define compiler/ linker options and filegroups for rules ###
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

### Library rules ###
cc_library(
	name = "DebugLib",
	srcs = ["lib/debug/debugUsb.c", "LufaSetupSrcs"],
	hdrs = ["lib/debug/debug.h", "LufaSetupHeaders"],

	copts = commonCopts + LUFA_COPTS,

	linkstatic = True,
	
	deps = ["@LUFA//:VirtualSerial"],
	
	visibility = [
		"//test:__pkg__",
		"//test:__subpackages__",
		"@CMock//CMock:__pkg__",
	],
)


cc_library(
	name = "I2cLib",
	srcs = glob(["lib/i2cmaster/*.c"]),
	hdrs = glob(["lib/i2cmaster/*.h"]),

	copts = commonCopts,

## For testing add '--define test=true ' to include MockLib ##
	deps = select({

        ":test": [
		],
        "//conditions:default": [],	
    }),

	visibility = [
		"//test:__pkg__",
		"//test:__subpackages__",
		"@CMock//CMock:__pkg__",
	],
)

cc_library(
	name = "DelayLib",
	srcs = ["lib/delay/user_delay.c"],
	hdrs = ["lib/delay/user_delay.h"],

	copts = commonCopts,

## For testing add '--define test=true ' to include MockLib ##
	deps = select({

        ":test": [
		],
        "//conditions:default": [],	
    }),

	visibility = [
		"//test:__pkg__",
		"//test:__subpackages__",
		"@CMock//CMock:__pkg__",
	],
)

cc_library(
	name = "TimerLib",
	srcs = ["lib/timer/timer.c"],
	hdrs = ["lib/timer/timer.h"],

	copts = commonCopts,
	deps = [
		":DebugLib",
	],
)

cc_library(
	name = "PAC1720DriverLib",
	srcs = ["lib/PAC1720_driver/PAC1720_driver.c"],
	hdrs = glob(["lib/PAC1720_driver/*.h"]),

	copts = commonCopts,

	deps = [
	],

	visibility = [
		"//test:__pkg__",
		"//test:__subpackages__",
		"@CMock//CMock:__pkg__",
	],
)

cc_library(
    name = "IncludeLib",
    hdrs = ["include/currentSenseApp.h"],

    copts = commonCopts,

    deps = [
		":DelayLib",
		":AdapterLib",
		":I2cLib",
		":DebugLib",
		":TimerLib",
    ],

	visibility = [
		"//test:__pkg__",
		"//test:__subpackages__",
		"@CMock//CMock:__pkg__",
	],
)

cc_library(
    name = "AdapterLib",
	srcs = ["src/adapter_PAC1720/adapter_PAC1720.c"],
    hdrs = ["src/adapter_PAC1720/adapter_PAC1720.h"],

    copts = commonCopts,

    deps = [
        ":PAC1720DriverLib",
    ],

	visibility = [
		"//test:__pkg__",
		"//test:__subpackages__",
		"@CMock//CMock:__pkg__",
	],
)

### Exports lib-files to allow test-package access ###
exports_files(
	glob([
		"lib/**/*.h",
	]),
	visibility = [
		"//test:__pkg__",
		"//test:__subpackages__",
		"@CMock//CMock:__pkg__",
	],
	
)

exports_files(
	glob([
		"src/*.c",
	]),
	visibility = [
		"//test:__pkg__",
		"//test:__subpackages__",
		"@CMock//CMock:__pkg__",
	],
	
)

### Create config to substitute dependencies in build process ###
### "--define test=true" appended to test call switches the actual dependencies ###
config_setting(
    name = "test",
    values = {
        "define": "test=true",
    },
)

### Binary rules ###


default_embedded_binary(
	name = "CurrentSenseApp",
	srcs = [
		"src/currentSenseApp.c",
    ],

	copts = commonCopts + LUFA_COPTS,

	linkopts = commonCopts + LUFA_COPTS + ["-Wl,-u,vfprintf -lprintf_flt -lm"],

	deps = [
        ":IncludeLib",
	],
)

default_embedded_binary(
	name = "FindSensorsApp",
	srcs = [
		"src/findSensorsApp.c",
    ],

	copts = commonCopts + LUFA_COPTS,

	linkopts = commonCopts + LUFA_COPTS + ["-Wl,-u,vfprintf -lprintf_flt -lm"],

	deps = [
        ":IncludeLib",
	],
)
