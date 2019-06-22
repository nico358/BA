load(
    "@EmbeddedSystemsBuildScripts//:unity.bzl",
    "generate_a_mock_for_every_file",
    "generate_a_unity_test_for_every_file",
    "mock",
    "unity_test",
)

# mock(
#     name = "CircBufMock",
#     srcs = ["//:lib/circular_buffer/circular_buffer.h"],
#     deps = ["//:CircularBufferLib"],
# )

unity_test(
    file_name = "sensor_driver_Test.c",
    deps = [
        "//:PAC1720DriverLib",
        "@CException",
        "@CMock",
    ],
)