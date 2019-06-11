package(default_visibility = ["//visibility:public"])

load(
    "@AvrToolchain//:helpers.bzl",
    "cpu_frequency_flag",
    "mcu_avr_gcc_flag"
)

commonCopts = mcu_avr_gcc_flag() + cpu_frequency_flag()

LUFA_COPTS = [
    "-Iexternal/LUFA/Demos/Device/ClassDriver/VirtualSerial/Config",
    "-isystem external/LUFA/"
]

filegroup(
    name = "LufaSetupSrcs",
    srcs = glob(["LUFA-Setup/*.c"])
)

filegroup(
    name = "LufaSetupHeaders",
    srcs = glob(["LUFA-Setup/*.h"])
)

cc_library(
    name = "IncludeLib",
    hdrs = [
        "currentSenseApp.h",
        "sensorController.h"
    ],

    copts = commonCopts,
    deps = [
        "//lib:DebugLib",
        "//lib:CurrentSenseLib",
        "//lib:CircularBufferLib",
        "//lib:CurrentMeasurementLib",
        "//lib:SensorAdapterLib",
        "//lib:I2cLib"
    ]
)