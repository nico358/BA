#include "unity.h"
#include "include/adapter_PAC1720.h"
#include "lib/i2cmaster/Mocki2cmaster.h"  
#include "lib/delay/Mockuser_delay.h" 
#include "lib/circular_buffer/Mockcircular_buffer.h" 

#include <stdio.h>

void test_fail(void){
    char msg[500];
    uint8_t x = 0;
    sprintf(msg, "Test: %x\n", x);
    // TEST_FAIL_MESSAGE(msg);
}

void test_adapter_i2c_write(void){
    // TEST_ASSERT_EQUAL(-1, adapter_i2c_write(0,0,NULL,0));
}