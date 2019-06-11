#include <util/delay.h>
#include <avr/io.h>
#include "lib/debug/debug.h"
#include "include/main.h"


int
main(void)
{
  debugInit(NULL);
  _delay_ms(1000);
  for(int i = 0; i < 10; i++){
    debugWriteLine("Running...\r\n");
    _delay_ms(500);
  }

  while (1)
  {

  }
  

}