#include "initallAll.h"

void initRCC_GPIOA(void);
void initRCC_GPIOE(void);
void initRCC_SYSCFG(void);
void initGPIO_OUT(void);
void initGPIO_IN(void);
void initSysTick(int currentFrequency);
void initEXTILine(void);
void initNVIC(void);

void initAll()
 {
	initRCC_GPIOA();
	initRCC_GPIOE();
	initRCC_SYSCFG();

	initGPIO_OUT();
	initGPIO_IN();

	__enable_irq();
	initSysTick(8000);
	initEXTILine();
	initNVIC();
}

void initRCC_GPIOA()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}

void initRCC_GPIOE()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
}

void initRCC_SYSCFG()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}

void initGPIO_OUT()
{
	GPIO_InitTypeDef gpioOUT;

	gpioOUT.GPIO_Mode = GPIO_Mode_OUT;
	gpioOUT.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpioOUT.GPIO_OType = GPIO_OType_PP;
	gpioOUT.GPIO_Speed = GPIO_Speed_2MHz;
	gpioOUT.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &gpioOUT);
}

void initGPIO_IN()
{
	GPIO_InitTypeDef gpioIN;

	gpioIN.GPIO_Mode = GPIO_Mode_IN;
	gpioIN.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	gpioIN.GPIO_Speed = GPIO_Speed_2MHz;
	gpioIN.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &gpioIN);
}

void initSysTick(int currentFrequency)
{
		SysTick->LOAD |= currentFrequency - 1;
		SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Pos;
		SysTick->CTRL |= SysTick_CTRL_COUNTFLAG_Pos;
		SysTick->CTRL |= ~SysTick_CTRL_ENABLE_Pos;
}

void initEXTILine()
{
	EXTI_InitTypeDef exti;

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	exti.EXTI_Line = EXTI_Line4;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
}

void initNVIC()
{
	NVIC_InitTypeDef nvic;

	nvic.NVIC_IRQChannel = EXTI4_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}
