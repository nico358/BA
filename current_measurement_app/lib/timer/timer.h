#include <avr/io.h>

/* Writes the CTC value */
void     TIM16_WriteOCRA3(uint16_t val);
/* Init timer, default CTC value: 8000 */
void     timer_init(void);
/* Stop timer, clear interrupts, reactivate wdt 500ms */
void     timer_stop(void);
/* Get counter value in us @8MHz */
uint16_t get_counter(void);
/* Reset counter 3*/
void     reset_counter(void);
/* Reset elapsed_ms*/
void     reset_timer(void);
/* Init counter, 1us @8Mhz */
void     counter_init(void);
/* Stop counter */
void     counter_stop(void);
/* timer: elapsed time in ms since init */
extern uint16_t elapsed_ms;