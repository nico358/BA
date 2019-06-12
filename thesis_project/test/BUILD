package(default_visbility = ["//visibility:public"])

load(
    "@EmbeddedSystemsBuildScripts//:unity.bzl",
    "generate_a_mock_for_every_file",
    "generate_a_unity_test_for_every_file",
    "mock",
    "unity_test",
)

mock(
    name = "CircularBufferMock",
    srcs = "//:lib/circular_buffer.h",
    #enforce_strict_ordering = True,
    deps = ["//:lib/CircularBufferLib"]
)

generate_a_mock_for_every_file(
    enforce_strict_ordering = True,
    file_list = [
        "//:lib/sensor-adapter/sensor_adapter.h"
    ],
    deps = [
        "//:lib/CircularBufferLib", 
		"//:lib/I2cLib", 
		"//:lib/CurrentMeasurementLib", 
		"//:lib/DebugLib"
    ]
)

unity_test(
    copts = [
        "-Wno-unused-function",
        "-Werror=return-type",
        "-Werror=discarded-qualifiers",
        "-Wno-error=incompatible-pointer-types",
        "-funsigned-char",
        "-std=gnu99",
    ],
    file_name = "MyTest.c",
    deps = [
        "//lib:DebugLib",
        "//lib:CircularBufferLib",
        "//lib:I2cLib",
        "//lib:SensorAdapterLib",
        "@CException",
        "@CMock",
    ],
)

generate_a_unity_test_for_every_file(
    file_list = glob(
        ["*_Test.c"],
    ),
    deps = [
        "//lib:DebugLib",
        "//lib:CircularBufferLib",
        "//lib:I2cLib",
        "//lib:SensorAdapterLib",
        "@CMock",
    ],
)

test_suite(
    name = "ALL",
    tests = [

    ]
)