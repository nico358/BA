#include "unity.h"
#include "lib/i2cmaster/Mocki2cmaster.h"  

void test_success(void){
    i2c_getData_ExpectAndReturn(0xBB);
}