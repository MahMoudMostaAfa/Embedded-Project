#ifndef SYSTICK_H
#define SYSTICK_H


void SysTick_Init() ;
void systick_wait_1ms();
void wait_ms(unsigned int time);
void wait_sec(unsigned int seconds);

#endif /*SYSTICK_H*/
