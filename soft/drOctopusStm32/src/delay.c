/**
 ******************************************************************************
 * @file    sysTick.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-08
 * @brief   Delay functions.
 ******************************************************************************
 */

#include "delay.h"
#include "config.h"
#include "stm32f30x.h"

// ---------- variables ----------
/**
 * Store time elapsed from start (in ms). 32bit gives only ~49 days so
 * 64bit is used - 580*10^6 years should be enough :)
 */
volatile uint64_t millisFromStart = 0;
/// Prescaler value for delay timer. Results in 1us clock period.
uint16_t delayTimerPrescaler1us;
/// Prescaler value for delay timer. Results in 256us clock period.
uint16_t delayTimerPrescaler256us;

// ---------- private functions declarations ----------
uint_fast8_t delayTimerReload(uint32_t ticks);

// ---------- public functions ----------
uint_fast8_t delayInit(void) {
	uint_fast8_t ret = 0;
	TIM_TimeBaseInitTypeDef tim;
	uint32_t prescaler;

	/* Calculate prescaler values. For system clock up to 216MHz and
	 * 16b prescaler, maximum timer clock period is 303us. */
	// 1us prescaler.
	delayTimerPrescaler1us = (SystemCoreClock + 1000000 / 2) / 1000000 - 1;
	// 256us prescaler
	prescaler = (SystemCoreClock + 1000000 / 256 / 2) * 256 / 1000000 - 1;
	if (prescaler > 65535) {
		// That should not happen if system clock frequency is less than 256MHz
		prescaler = 65535;
		ret = 1; // signal error
	}
	delayTimerPrescaler256us = prescaler;

	// Delay timer initialization.
	TIM_Cmd(DELAY_TIMER, DISABLE);
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Down;
	tim.TIM_Period = 1;
	// Preload 1us prescaler to not extend 1us delay too much.
	tim.TIM_Prescaler = delayTimerPrescaler1us;
	TIM_TimeBaseInit(DELAY_TIMER, &tim);
	// Setup timer to generate single pulse.
	TIM_SelectOnePulseMode(DELAY_TIMER, TIM_OPMode_Single);

	// Initialize SysTick to generate IRQ every 1ms.
	if (SysTick_Config((SystemCoreClock + 500) / 1000)) {
		ret = 2;
	}
	return ret;
}

uint_fast8_t delayMs(uint32_t time) {
	uint64_t end;
	//delayTimerReload(sysTickForMs);
	end = millisFromStart + time;
	while (millisFromStart < end) {
	}
	return 0;
}

uint_fast8_t delayUs(uint32_t time) {
	// Disable timer.
	DELAY_TIMER->CR1 = TIM_OPMode_Single | TIM_CounterMode_Down;
	DELAY_TIMER->CNT = time-1; // Load new time
	DELAY_TIMER->SR = (uint16_t) ~TIM_FLAG_Update; // Clear timer update flag.
	// Enable timer.
	DELAY_TIMER->CR1 = TIM_OPMode_Single | TIM_CounterMode_Down | TIM_CR1_CEN;
	while ((DELAY_TIMER->SR & TIM_FLAG_Update) == 0) {
		// Wait until timer update flag is set.
	}
	DELAY_TIMER->SR = (uint16_t) ~TIM_FLAG_Update; // Clear timer update flag.
	return 0;
}

uint64_t getTime() {
	return millisFromStart;
}

/**
 * Interrupt handler.
 */
void SysTick_Handler() {
	millisFromStart++;
}

// ---------- private functions ----------

uint_fast8_t delayTimerReload(uint32_t ticks) {
	uint_fast8_t ret = 0;
	TIM_TimeBaseInitTypeDef tim;
	uint32_t prescaler;

	TIM_Cmd(DELAY_TIMER, DISABLE);

	// init timer
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Down;
	tim.TIM_Period = ticks - 1;
	tim.TIM_Prescaler = delayTimerPrescaler1us;
	TIM_TimeBaseInit(DELAY_TIMER, &tim);

	TIM_Cmd(DELAY_TIMER, ENABLE);

	return ret;
}
// ---------- test functions ----------
#if TEST_MODE == TEST_MODE_DELAY
#include <stdlib.h>
#include "outputs.h"

#if HW_VERSION == HW_VERSION0
#define LED_GPIO GPIOA
#define LED_PIN GPIO_Pin_5
#else
#error "Unsupported HW version!"
#endif /* HW_VERSION == HW_VERSION0 */

/**
 * Delay test mode main function. Generate 10us and 1ms LED pulses with random
 * delays between pulse pairs.
 * @return
 */
int main(void) {
	int i, max;

	defaultInit();

	for (;;) {
		// ledCmd(0, ENABLE); optimize:
		// GPIO_WriteBit(ledGpios[0], ledPins[0], 1); optimize:
		LED_GPIO->BSRR = GPIO_Pin_5;
		delayUs(1);
		// ledCmd(0, DISABLE); optimize:
		// GPIO_WriteBit(ledGpios[0], ledPins[0], 0);
		LED_GPIO->BRR = GPIO_Pin_5;

		delayUs(10);
		// ledCmd(0, ENABLE); optimize:
		// GPIO_WriteBit(ledGpios[0], ledPins[0], 1); optimize:
		LED_GPIO->BSRR = GPIO_Pin_5;
		delayUs(100);
		// ledCmd(0, DISABLE); optimize:
		// GPIO_WriteBit(ledGpios[0], ledPins[0], 0);
		LED_GPIO->BRR = GPIO_Pin_5;

		delayUs(10);
		// ledCmd(0, ENABLE); optimize:
		// GPIO_WriteBit(ledGpios[0], ledPins[0], 1); optimize:
		LED_GPIO->BSRR = GPIO_Pin_5;
		delayMs(1);
		// ledCmd(0, DISABLE); optimize:
		// GPIO_WriteBit(ledGpios[0], ledPins[0], 0);
		LED_GPIO->BRR = GPIO_Pin_5;

		max = rand() & 0xfff;
		for (i = 0; i < max; i++) {
		}
	}
}

#endif /* TEST_MODE == TEST_MODE_DELAY */
