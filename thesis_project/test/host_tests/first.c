#include "unity.h"
#include "CException.h"
#include <stdio.h>

#define true 1

int main(void){
    setUp();

char msg[100];
sprintf(msg, "Hello %d\r\n", 13);
printf(msg);

    tearDown();


}
