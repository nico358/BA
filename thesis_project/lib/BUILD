load(
    "@AvrToolchain//:helpers.bzl",
    "cpu_frequency_flag",
    "create_unity_library",
    "default_embedded_binary",
    "generate_hex",
    "mcu_avr_gcc_flag",
)

LUFA_COPTS = [
    "-Iexternal/LUFA/Demos/Device/ClassDriver/VirtualSerial/Config",
    "-isystem external/LUFA/",
    # "-Iexternal/LUFA/Demos/Device/ClassDriver/VirtualSerial/Config/",
]

cc_library(
    name = "DebugLib",
    srcs = [
        "LUFA-Setup/Helpers.c",
        "debug/debugUsb.c",
    ],
    hdrs = glob(["debug/*.h"]) + ["LUFA-Setup/Helpers.h"],
    copts = mcu_avr_gcc_flag() + cpu_frequency_flag() + LUFA_COPTS,
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = ["@LUFA//:VirtualSerial"],
)



cc_library(
    name = "gpio",
    srcs = ["gpio/gpio.c"],
    hdrs = ["gpio/gpio.h"],
    visibility = ["//visibility:public"],
    deps = [":DebugLib"],
)
