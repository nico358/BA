#include <stdio.h>
#include <stdint.h>
#include "CException.h"

int
main(void)
{
  printf("Test binary\r\n");
  printf("size: %lu byte\n", sizeof(CEXCEPTION_T));
}