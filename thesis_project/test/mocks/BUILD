cc_library(
    name = "ExtMockLib",
    srcs = [
        "lib/i2cmaster/twimaster.c",
    ],
    hdrs = [
        "compat/twi.h",
        "util/twi.h",
        "util/delay_basic.h",
        "util/delay.h",
        "avr/io.h",
        "avr/portpins.h",
        "avr/common.h",
        "avr/version.h",
        "avr/fuse.h",
        "avr/lock.h",
        "avr/sfr_defs.h",
        "avr/iom32u4.h",
        "avr/interrupt.h", 
        "inttypes.h",
        "math.h",
        "lib/i2cmaster/i2cmaster.h",

    ],
    visibility = ["//visibility:public"],
    deps = [
        "@CMock",
        "@CException",
    ],
)