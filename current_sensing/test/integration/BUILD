load(
    "@EmbeddedSystemsBuildScripts//:unity.bzl",
    "generate_a_mock_for_every_file",
    "generate_a_unity_test_for_every_file",
    "mock",
    "unity_test",
)


unity_test(
    file_name = "sensor_integration_Test.c",
    deps = [
        "//:AdapterLib",
        "@CException",
    ]
)
