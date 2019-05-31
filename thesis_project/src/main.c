#include "BazelTemplate/Functions.h"
#include <util/delay.h>
#include <avr/io.h>
#include "lib/debug/debug.h"
#include "include/main.h"


int
main(void)
{
  debugInit(NULL);
  _delay_ms(1000);
  int x = add(1,2);

  while (1)
  {
    debugWriteLine("Running...");
    _delay_ms(500);
  }
  

}