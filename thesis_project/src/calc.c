#include <stdio.h>
#include <stdint.h>
#include "lib/PAC1720_driver/PAC1720_driver.h"

typedef void (*fptr)(void);

struct x {
fptr y;
uint8_t z;
};


int main(void){

static struct PAC1720_device dev;

struct x x;

char msg[128];
sprintf(msg, "%p %d\r\n", x.y, x.z);
printf(msg);

sprintf(msg, "%p %p %p %p\r\n", &dev, dev.write, dev.read, dev.delay_ms);
printf(msg);
}