#pragma once

#ifndef __AVR_ATmega32U4__
    #include "util/twi.h"
#else
    #include <util/twi.h>
#endif
#include <stdint.h>

#include "lib/circular_buffer/circular_buffer.h"
#include "lib/debug/debug.h"
#include "lib/i2cmaster/i2cmaster.h"

