#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
// #include "lib/PAC1720_driver/PAC1720_driver.h"

typedef void (*fptr)(void);
struct x* getptr(void);

struct x {
fptr y;
uint8_t z;
};


int main(void){

struct x* x = getptr();
x->y = &getptr;
x->z = 9;

char msg[128];
sprintf(msg, "%p ,x.y = %p, x.z = %d, %p, y.y = %p, y.z = %d\r\n", x, x->y, x->z, w, w->y, w->z);
printf(msg);

}

