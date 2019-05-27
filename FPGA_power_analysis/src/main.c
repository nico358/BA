#include "BazelTemplate/Functions.h"
#include <util/delay.h>
#include <avr/io.h>
#include "lib/debug/debug.h"
int
main(void)
{
  DDRB |= _BV(PB5);
  PORTB |= _BV(PB5);
  debugInit(NULL);
  _delay_ms(1000);
  int x = add(1,2);

  while (1)
  {
    debugWriteLine("Running...");
    _delay_ms(500);
  }

}