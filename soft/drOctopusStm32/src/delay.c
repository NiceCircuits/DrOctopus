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

// ---------- Private variables ----------
/**
 * Store time elapsed from start (in ms). 32bit gives only ~49 days so
 * 64bit is used - 580*10^6 years should be enough :)
 */
volatile uint64_t millisFromStart = 0;
/// Prescaler value for delay timer. Results in 1us clock period.
uint16_t delayTimerPrescalerUs;
/// Prescaler value for delay timer. Results in 250us clock period.
uint16_t delayTimerPrescalerMs;
/// Value divider for delayMs function.
#define DELAY_MS_DIVIDER (4)
/// Maximum delay time for delayMs function.
#define DELAY_MS_MAX (65536 / DELAY_MS_DIVIDER)

// ---------- public functions ----------
uint_fast8_t delayInit(void) {
	uint_fast8_t ret = 0;
	TIM_TimeBaseInitTypeDef tim;
	uint32_t prescaler;

	/* Calculate prescaler values. For system clock up to 216MHz and
	 * 16b prescaler, maximum timer clock period is 303us. */
	// 1us prescaler.
	delayTimerPrescalerUs = (uint16_t) ((SystemCoreClock + 1000000 / 2)
			/ 1000000 - 1);
	// 256us prescaler
	prescaler = (SystemCoreClock + 1000 * DELAY_MS_DIVIDER / 2)
			/ DELAY_MS_DIVIDER / 1000 - 1;
	if (prescaler > 65535) {
		// That should not happen if system clock frequency is less than 256MHz
		prescaler = 65535;
		ret = 1; // signal error
	}
	delayTimerPrescalerMs = (uint16_t)prescaler;

	// Delay timer initialization.
	TIM_Cmd(DELAY_TIMER, DISABLE);
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Down;
	tim.TIM_Period = 1;
	// Preload 1us prescaler to not extend 1us delay too much.
	tim.TIM_Prescaler = delayTimerPrescalerUs;
	TIM_TimeBaseInit(DELAY_TIMER, &tim);
	// Setup timer to generate single pulse.
	TIM_SelectOnePulseMode(DELAY_TIMER, TIM_OPMode_Single);

	// Initialize SysTick to generate IRQ every 1ms.
	if (SysTick_Config((SystemCoreClock + 500) / 1000)) {
		ret = 2;
	}
	return ret;
}

uint_fast8_t delayMs(uint16_t time) {
	timerStartMs(time);
	while (timerEnd() == 0) {
	}
	return 0;
}

uint_fast8_t delayUs(uint16_t time) {
	// Disable timer.
	DELAY_TIMER->CR1 = TIM_OPMode_Single | TIM_CounterMode_Down;
	DELAY_TIMER->CNT = time - 1U; // Load new time
	DELAY_TIMER->SR = (uint16_t) ~TIM_FLAG_Update; // Clear timer update flag.
	// Enable timer.
	DELAY_TIMER->CR1 = TIM_OPMode_Single | TIM_CounterMode_Down | TIM_CR1_CEN;
	while ((DELAY_TIMER->SR & TIM_FLAG_Update) == 0) {
		// Wait until timer update flag is set.
	}
	DELAY_TIMER->SR = (uint16_t) ~TIM_FLAG_Update; // Clear timer update flag.
	return 0;
}

uint_fast8_t timerStartUs(uint16_t time) {
	// Disable timer.
	DELAY_TIMER->CR1 = TIM_OPMode_Single | TIM_CounterMode_Down;
	DELAY_TIMER->CNT = time - 1U; // Load new time
	DELAY_TIMER->SR = (uint16_t) ~TIM_FLAG_Update; // Clear timer update flag.
	// Enable timer.
	DELAY_TIMER->CR1 = TIM_OPMode_Single | TIM_CounterMode_Down | TIM_CR1_CEN;
	return 0;
}

uint_fast8_t timerStartMs(uint16_t time) {
	if (time > DELAY_MS_MAX) {
		time = DELAY_MS_MAX;
	}
	// Disable timer.
	DELAY_TIMER->CR1 = TIM_OPMode_Single | TIM_CounterMode_Down;
	// Set prescaler to achieve 250us clock period.
	TIM_PrescalerConfig(DELAY_TIMER, delayTimerPrescalerMs,
	TIM_PSCReloadMode_Immediate);
	DELAY_TIMER->CNT = time * (uint32_t)DELAY_MS_DIVIDER - 1U; // Load new time
	DELAY_TIMER->SR = (uint16_t) ~TIM_FLAG_Update; // Clear timer update flag.
	// Enable timer.
	DELAY_TIMER->CR1 = TIM_OPMode_Single | TIM_CounterMode_Down | TIM_CR1_CEN;
	return 0;
}

uint_fast8_t timerEnd(void) {
	if ((DELAY_TIMER->SR & TIM_FLAG_Update) == 0) {
		// not finished
		return 0;
	} else {
		// Reload default prescaler.
		TIM_PrescalerConfig(DELAY_TIMER, delayTimerPrescalerUs,
		TIM_PSCReloadMode_Immediate);
		return 1;
	}
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

// ---------- test functions ----------
#if defined(TEST_MODE) && TEST_MODE == TEST_MODE_DELAY
#include <stdlib.h>
#include "outputs.h"

#if defined(HW_VERSION) && HW_VERSION == HW_VERSION0
#define LED_GPIO GPIOA
#define LED_PIN GPIO_Pin_5
#elif defined(HW_VERSION) && HW_VERSION == HW_VERSION1
#define LED_GPIO GPIOB
#define LED_PIN GPIO_Pin_12
#else
#error "Unsupported HW version!"
#endif /* HW_VERSION == HW_VERSION0 */

/**
 * Delay test mode main function. Generate pulses: 1us H, 10us L, 100us H,
 * 1ms L, 10ms H, random ~0..2ms L.
 * @return
 */
int main(void) {
	int i, max;

	defaultInit();

	for (;;) {
		// LED_PIN -> High state
		LED_GPIO->BSRR = LED_PIN;
		delayUs(1);

		timerStartUs(10);
		// LED_PIN -> Low state
		LED_GPIO->BRR = LED_PIN;
		while (timerEnd() == 0) {
		}

		// LED_PIN -> High state
		LED_GPIO->BSRR = LED_PIN;
		delayUs(100);

		timerStartMs(1);
		// LED_PIN -> Low state
		LED_GPIO->BRR = LED_PIN;
		while (timerEnd() == 0) {
		}

		// LED_PIN -> High state
		LED_GPIO->BSRR = LED_PIN;
		delayMs(10);
		// LED_PIN -> Low state
		LED_GPIO->BRR = LED_PIN;

		max = rand() & 0x3fff;
		for (i = 0; i < max; i++) {
			// Dummy to force to not optimize out.
			LED_GPIO->BRR = LED_PIN;
		}
	}
}

#endif /* TEST_MODE == TEST_MODE_DELAY */
