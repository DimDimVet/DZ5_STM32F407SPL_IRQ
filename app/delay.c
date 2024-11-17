#include "stm32f4xx.h"

volatile uint32_t delayCnt = 0;

void delay(uint32_t delayMs) {
	delayCnt = delayMs;
	while (delayCnt) {
	};
}

void SysTick_Handler() {
	if (delayCnt != 0) {
		delayCnt--;
	};
}
