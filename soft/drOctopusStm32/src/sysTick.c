/**
 ******************************************************************************
 * @file    sysTick.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-08
 * @brief   System clock functions
 ******************************************************************************
 */

#include "sysTick.h"
#include "config.h"
#include "stm32f30x.h"

/**
 * Store time elapsed from start (in ms). 32bit gives only ~49 days so 64bit
 * is used - 580*10^6 years should be enough :)
 */
volatile uint64_t millisFromStart = 0;

uint_fast8_t sysTickInit(void) {
	return SysTick_Config(SystemCoreClock / 1000);
}

void SysTick_Handler() {
	millisFromStart++;
}

uint_fast8_t delayMs(uint32_t time) {
	uint64_t end = millisFromStart + time;
	while (millisFromStart < end) {
	}
	return 0;
}
