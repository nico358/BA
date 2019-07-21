#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "lib/debug/debug.h"
#include <avr/power.h>
#include <avr/wdt.h>


static uint64_t mseconds = 0;
char msg[64];

int main(void){
    
    
    debugInit(NULL);

    // cli();
    // wdt_reset();
    // /* Clear WDRF in MCUSR */
    // MCUSR &= ~(1<<WDRF);
    // /* Write logical one to WDCE and WDE */
    // /* Keep old prescaler setting to prevent
    // unintentional time-out */
    // WDTCSR |= (1<<WDCE) | (1<<WDE);
    // /* Turn off WDT */
    // WDTCSR = 0x00;
    // sei();

    wdt_disable();
    // clock_prescale_set(1);

    /* Clear TIM1 Bit in Power Reduction Register */
	PRR1   &= ~(_BV(PRTIM3));
    /* Output Compare A Match Interrupt Enable */
    TIMSK3 |= _BV(OCIE3A);// | _BV(TOIE1);
    /* WGM bit: CTC mode, top by OCR1A, clock select bit: no prescaling */
	TCCR3B |= _BV(WGM12) | _BV(CS10);
    /* 8MHz/1*8000 = 1000Hz time counter freq */
    uint8_t sreg = SREG;
    cli();
	/* Set TCNT1 to i */
	OCR3A = 8000;
    SREG = sreg;
    sei();

    for(;;){

    }

}

ISR(TIMER3_COMPA_vect){
	uint8_t sreg = SREG;
    cli();
    mseconds++;
    if((mseconds % 1000) == 0){
        sprintf(msg, "Elapsed: %lu\r\n", mseconds);
        debugWriteLine(msg);
    }
    SREG = sreg;
    sei();
}
