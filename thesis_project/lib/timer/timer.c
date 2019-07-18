#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "timer.h"

uint16_t elapsed_ms;

ISR(TIMER3_COMPA_vect){
	cli();
    elapsed_ms++;
	sei();
}

ISR(TIMER3_OVF_vect){
    cli();
    elapsed_ms++;
	sei();
}


void TIM16_WriteOCRA3(uint16_t val){
	cli();
	/* Set TCNT1 to val */
	OCR3A = val;
	sei();
}

uint16_t TIM16_ReadTCNT3(void)
{
    uint16_t reg;
    cli();
    /* Read TCNT1 */
    reg = TCNT3;
    sei();
    return reg;
}

void TIM16_WriteTCNT3( unsigned int val )
{
    cli();
    /* Set TCNTn to reg */
    TCNT3 = val;
    sei();
}

void timer_init(void){
    wdt_disable();
	/* Clear TIM1 Bit in Power Reduction Register */
	PRR1   &= ~(_BV(PRTIM3));
   /* Output Compare A Match Interrupt Enable */
    TIMSK3 |= _BV(OCIE3A);
    /* WGM bit: CTC mode, top by OCR1A, clock select bit: no prescaling */
	TCCR3B |= _BV(WGM12) | _BV(CS10);
    /* 8MHz/1*8000 = 1000Hz counter freq */
    TIM16_WriteOCRA3(8000);
    elapsed_ms = 0;
}

void timer_stop(void){
    TCCR3B = 0x00;
    TIMSK3 &= ~(_BV(OCIE3A));
    PRR1   |= _BV(PRTIM3);
    TIM16_WriteOCRA3(0);
    wdt_enable(WDTO_500MS);
}
