load(
    "@EmbeddedSystemsBuildScripts//:unity.bzl",
    "generate_test_runner",
    "unity_test",
)
load(
    "@AvrToolchain//:helpers.bzl",
    "cpu_frequency_flag",
    "create_unity_library",
    "default_embedded_binary",
    "generate_hex",
    "mcu_avr_gcc_flag",
)

cc_library(
    name = "MyEmbeddedLib",
    srcs = ["src/Functions.c"],
    hdrs = ["BazelTemplate/Functions.h"],
    deps = ["@CException"],
)


LUFA_COPTS = [
    "-Iexternal/LUFA/Demos/Device/ClassDriver/VirtualSerial/Config",
    "-isystem external/LUFA/",
    # "-Iexternal/LUFA/Demos/Device/ClassDriver/VirtualSerial/Config/",
]

# lib definitions
cc_library(
	name = "DebugLib",
	srcs = ["lib/debug/debugUsb.c", "lib/LUFA-Setup/Helpers.c"],
	hdrs = glob(["lib/debug/*.h"]) + ["lib/LUFA-Setup/Helpers.h"],

	visibility = ["//visibility:public"],

	copts = mcu_avr_gcc_flag() + cpu_frequency_flag() + LUFA_COPTS,
	linkstatic = True,
	deps = ["@LUFA//:VirtualSerial"],
)

default_embedded_binary(
    name = "MyApp",
    srcs = ["src/main.c"],
    copts = mcu_avr_gcc_flag() + cpu_frequency_flag(),
    linkopts = mcu_avr_gcc_flag(),
    deps = [
        ":DebugLib",
        ":MyEmbeddedLib",
        "@CException",
    ],
)

#cc_binary(
#    name = "Print",
#    srcs = ["src/print.c"],
#    deps = [":MyEmbeddedLib"],
#)

unity_test(
    copts = mcu_avr_gcc_flag() + cpu_frequency_flag(),
    file_name = "test/MyTest.c",
    linkopts = mcu_avr_gcc_flag() + cpu_frequency_flag(),
    deps = [":MyEmbeddedLib"],
)

generate_test_runner(
    name = "embeddedTestRunner",
    cexception = False,
    file_name = "test/MyTest.c",
)

default_embedded_binary(
    name = "embeddedTest",
    srcs = [
        "test/MyTest.c",
        ":embeddedTestRunner",
    ],
    copts = mcu_avr_gcc_flag() + cpu_frequency_flag(),
    linkopts = mcu_avr_gcc_flag() + cpu_frequency_flag(),
    deps = [
        ":MyEmbeddedLib",
        ":Unity",
    ],
)

create_unity_library(
    name = "Unity",
)
