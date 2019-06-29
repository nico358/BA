load(
    "@EmbeddedSystemsBuildScripts//:unity.bzl",
    "generate_a_mock_for_every_file",
    "generate_a_unity_test_for_every_file",
    "mock",
    "unity_test",
)

mock(
    name = "DriverMock",
    srcs = [
        "//:lib/PAC1720_driver/PAC1720_driver.h", 
        "//:lib/PAC1720_driver/PAC1720_definitions.h",
    ],
    deps = ["//:PAC1720DriverLib"],
)

unity_test(
    file_name = "sensor_driver_Test.c",
    deps = [
        "//:PAC1720DriverLib",
        "@CException",
    ],
)

unity_test(
    file_name = "sensor_adapter_Test.c",
    deps = [
        "//:AdapterLib",
        "@CException",
    ],
)
