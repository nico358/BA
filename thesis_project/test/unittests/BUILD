load(
    "@EmbeddedSystemsBuildScripts//:unity.bzl",
    "generate_a_mock_for_every_file",
    "generate_a_unity_test_for_every_file",
    "mock",
    "unity_test",
)

mock(
    name = "I2CMock",
    srcs = ["//:lib/i2cmaster/i2cmaster.h"],
    deps = ["//:I2cLib"],
)

unity_test(
    file_name = "sensor_adapter_Test.c",
    deps = [
        ":I2CMock",
        # "@ExtMockLib",
        "//:PAC1720DriverLib",
        "@CException",
        "@CMock",
    ],
)

unity_test(
    file_name = "sensor_driver_Test.c",
    deps = [
        "//:PAC1720DriverLib",
        "@CException",
        "@CMock",
    ],
)