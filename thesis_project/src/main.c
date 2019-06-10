#include <util/delay.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/io.h>
#include "lib/debug/debug.h"
#include "lib/current_sense/current_sense.h"
#include "lib/current_sense/current_measurement.h"
#include <avr/io.h>


int main(void) 
{
  int finished;
  debugInit(NULL);
  // init buffer, i2c, set timer mode to ctc, set ocr to 1250 (?), 
  // enables output compare match interrupt, ISR(TIMER3_COMPA_vect) sets currentSenseFlag and executes currentSenseTask()
  initCurrentSense();
  // select i2c address of sensor, select channel (1:2), write config:
  // CURRENT_RATE_CONFIG 0b11 Continuous conversion
  // CURRENT_AVERAGING_CONFIG 0b00 	// No averaging
  // CURRENT_SAMPLING_CONFIG 0b101 	// Measurement accuracy:
  // 80 	101 2047	12
  // 40	100 1023	11
  // 20	011 511		10
  // 10 	010 255		9
  // 5	001 127		8
  // 2.5 	000 63		7
  // CURRENT_RANGE_CONFIG 0b11 		// Full swing +-80mV
  currentSenseConfig();
  // set wdt reset flag
  MCUSR &= ~(1 << WDRF);
  wdt_disable();
  // disable prescaler
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
            printCurrent(CURRENT_MONITOR);
            printCurrent(CURRENT_WIRELESS);
            printCurrent(CURRENT_MCU);
            printCurrent(CURRENT_FPGA_VCCINT);
            printCurrent(CURRENT_FPGA_VCCAUX);

            debugNewLine();
            break;

          case 'F':
            debugWriteChar(data);
            findCurrentSensors();
            break;

          case 'M':
            debugWriteChar(data);
            currentSenseClearMeasurements();
            // set TCCR3B clock select to clkio/1024
            currentSenseBegin();
            break;

          case 'm':
            debugWriteChar(data);
            // set TCCR3B to stop (000)
            currentSenseEnd();
            break;

          case 'f':
            debugWriteChar(data);
            currentMeasurementFloat current = fetchCurrentMeasurementFloat();
            debugWriteStringLength((char*) current.measurements, sizeof(currentMeasurementFloat));
            break;

          case 'q':
            finished = 1;
            break;

      }
    }
  }
  return 0;
}