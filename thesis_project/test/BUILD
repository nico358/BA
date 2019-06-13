load(
    "@EmbeddedSystemsBuildScripts//:unity.bzl",
    "generate_a_unity_test_for_every_file",
    "mock",
    "unity_test",
)

generate_a_unity_test_for_every_file(
    file_list = glob(
        ["*_Test.c"],
    ),
    deps = [
        "//:BazelTemplate",
        "@CMock",
        "@CException",
    ],
)

test_suite(
    name = "ALL",
    tests = [
        ":My_Test",
    ],
)