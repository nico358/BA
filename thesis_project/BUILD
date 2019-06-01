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
    deps = [
        "@CException",
        ":DebugLib"
    ],
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

cc_library(
    name = "MainHeader",
    srcs = [
        "include/main.h",
    ],
)

default_embedded_binary(
    name = "MyApp",
    srcs = ["src/main.c"],
    copts = mcu_avr_gcc_flag() + cpu_frequency_flag(),
    linkopts = mcu_avr_gcc_flag(),
    deps = [
        ":MainHeader",
        ":DebugLib",
        ":MyEmbeddedLib",
        "@CException",
    ],
    visibility = ["//test:__pkg__"],
)

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

#use on platform with bazel build embeddedTest --config=motherboard
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
    visibility = ["//visibility:public"],
)

create_unity_library(
    name = "Unity",
)

#example binary rule
#cc_binary(
#    name = "Print",
#    srcs = ["test/print.c"],
#    deps = [":MyEmbeddedLib"],
#    visibility = ["//visibility:public"],
#)

#cc_binary(
#    name = "First",
#    srcs = ["test/first.c"],
#    deps = [
#        ":MyEmbeddedLib",
#        ":Unity",
#        "@CException",
#    ],
#    visibility = ["//visibility:public"],
#)

#package(default_visibility = ["//visibility:public"])
#runs without main function if compiled inside /test folder
#runs with main function from root (core dump in logfile)
#cc_test(
#    name = "MyTest",
#    srcs = ["test/MyTest.c"],
#    deps = [
#        ":Unity",
#        ":MyEmbeddedLib",
#    ],
#)

cc_test(
    name = "First",
    srcs = ["test/host_tests/first.c"],
    deps = [
        ":Unity",
        "@CException",
    ],
)
