#include <avr/io.h>
#include "lib/debug/debug.h"

void foo(uint8_t){
   debugWriteLine("DUT called/n");
}