#include <avr/io.h>

/* Writes the CTC value */
void     TIM16_WriteOCRA1(uint16_t j);
/* Writes a counter value */
void     TIM16_WriteTCNT1(unsigned int reg);
/* Gets the counter value */
uint16_t TIM16_ReadTCNT1(void);
/* Init timer, default CTC value: 8000 */
void     timer_init(void);
/* Stop timer, clear interrupts, reactivate wdt 500ms */
void     timer_stop(void);

/* time in ms since init */
extern uint16_t elapsed_ms;