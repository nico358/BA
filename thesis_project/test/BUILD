load(
    "@EmbeddedSystemsBuildScripts//:unity.bzl",
    "generate_a_unity_test_for_every_file",
    "mock",
    "unity_test",
)

unity_test(
    file_name = "My_Test.c",
    deps = [
        "@CException",
        "//:SensorAdapterLib",
    ],
)

test_suite(
    name = "ALL",
    tests = [
        ":My_Test",
    ],
)
