cc_library(
    name = "ExtMockLib",
    # srcs = ["i2cmaster/Mocki2cmaster.c"],
    hdrs = [
        "compat/twi.h",
        "util/twi.h",
        "avr/io.h",
        "avr/portpins.h",
        "avr/common.h",
        "avr/version.h",
        "avr/fuse.h",
        "avr/lock.h",
        "avr/sfr_defs.h",
        "avr/iom32u4.h",
        # "i2cmaster/Mocki2cmaster.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@CMock",
    ],
)