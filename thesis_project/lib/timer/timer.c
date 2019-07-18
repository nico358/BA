#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "timer.h"

/* Writes a counter value */
void     TIM16_WriteTCNT1(uint16_t val);
/* Gets the counter value */
uint16_t TIM16_ReadTCNT1(void);

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
	/* Set TCNT3 to val */
	OCR3A = val;
	sei();
}

uint16_t TIM16_ReadTCNT1(void)
{
    uint16_t reg;
    cli();
    /* Read TCNT1 */
    reg = TCNT1;
    sei();
    return reg;
}

void TIM16_WriteTCNT1(uint16_t val)
{
    cli();
    /* Set TCNTn to reg */
    TCNT1 = val;
    sei();
}

uint16_t get_counter(void)
{
    return TIM16_ReadTCNT1();
}

void reset_counter(void)
{
    TIM16_WriteTCNT1(0);
}

void timer_init(void){
    wdt_disable();
	/* Clear TIM1 Bit in Power Reduction Register */
	PRR1   &= ~(_BV(PRTIM3));
   /* Output Compare A Match Interrupt Enable */
    TIMSK3 |= _BV(OCIE3A);
    /* WGM bit: CTC mode, top by OCR1A, clock select bit: no prescaling */
	TCCR3B |= _BV(WGM32) | _BV(CS30);
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

void counter_init(void){
	/* Clear TIM1 Bit in Power Reduction Register */
	PRR0   &= ~(_BV(PRTIM1));
    /* Clock select bit: prescaling = 8 */
	TCCR1B |= _BV(CS11);
}

void counter_stop(void){
    TCCR1B = 0x00;
    PRR0   |= _BV(PRTIM1);
}
