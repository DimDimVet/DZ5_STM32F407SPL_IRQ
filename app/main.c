#include "initallAll.h"
#include "delay.h"
#include "stdbool.h"

// LED2 PA6 31pin соотв. GPIO port mode register (GPIOx_MODER) 12-13 битам
// LED3 PA7 32pin соотв. GPIO port mode register (GPIOx_MODER) 14-15 битам
// Button1 PE3
// Button0 PE4

bool isFlag=false;

int main(void) {

	initAll();

	while (1) {
		if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
		}
		else
		{
			delay(500);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			if(isFlag){GPIO_ResetBits(GPIOA, GPIO_Pin_7);}
			else{GPIO_SetBits(GPIOA, GPIO_Pin_7);}

			delay(500);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
			if(isFlag){GPIO_SetBits(GPIOA, GPIO_Pin_7);}
			else{GPIO_SetBits(GPIOA, GPIO_Pin_7);}
		}
	}
}

void EXTI4_IRQHandler()
{
	EXTI_ClearFlag(EXTI_Line4);

	isFlag=!isFlag;
}
