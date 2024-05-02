#include "tm4c123gh6pm"
#include <stdint.h>

void SysTick_Init() // To initialize SysTick Counter
{
	NVIC_ST_CTLR_R = 0;
	NVIC_ST_RELOAD_R = 1;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTLR_R = 0X05;
}

void SysTick_wait_1ms() // for 1 milli second Delay
{
	SysTick_Init();
	NVIC_ST_RELOAD_R = 16000 - 1; // (16MHz * 10^-3(ms)) -1
	while((NVIC_ST_CTLR_R & 0x00010000) == 0){}; // wait
	}

void SysTick_wait_1sec()
{
	SysTick_Init();
	NVIC_ST_RELOAD_R = 16,000,000 - 1;(16MHz * 1sec) -1
	while((NVIC_ST_CTLR_R & 0x00010000) == 0){}; // wait
	}

	void general_delay_ms(uint32_t num_of_ms) // for a delay that is multiple of 1ms
	{
		uint32_t i;
		for(i=0;i<num_of_ms;i++)
				SysTick_wait_1ms();
	}
	
	void general_delay_sec(uint32_t num_of_sec) // for a delay that is multiple of 1sec
	{
		uint32_t i;
		for(i=0;i<num_of_sec;i++)
				SysTick_wait_1sec();
	}
		
		