#include <util/delay.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/io.h>
#include "lib/debug/debug.h"
#include "lib/current_sense/current_sense.h"
#include "lib/current_sense/current_measurement.h"


int main(void) 
{
  int finished;
  debugInit(NULL);
  initCurrentSense();
  currentSenseConfig();
  MCUSR &= ~(1 << WDRF);
  wdt_disable();
  clock_prescale_set(clock_div_1);

  finished = 0;
  while (!finished)
  {

    _delay_ms(1000);
    debugWriteLine("Running...\r\n");
    debugReadChar();

    if(debugReadCharAvailable())
    {
      uint8_t data = debugGetChar();
      switch(data)
      {
          case 'C': 
            debugWriteString("Config: ");
            debugWriteBin8(CURRENT_CONFIG);
            debugWriteChar(' ');
            debugWriteDec16(CURRENT_SENSE_OCR);
            debugNewLine();

            printCurrent(CURRENT_USB);
            print
      }
    }
  }
  

}