#include <stdio.h>
#include <stdint.h>

int main(void){

uint8_t arr[5] = {1,2,3,4,5};
uint8_t *ptr = arr;
print(*ptr, *ptr++);


}

void print(uint8_t a, uint8_t b){
char msg[128];
sprintf(msg, "a: %d b: %d \r\n", a, b);
printf(msg);
}