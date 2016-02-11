/**
 ******************************************************************************
 * @file    main.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-07
 * @brief   main.c for drOctopus firmware for STM32
 ******************************************************************************
 */

#include "stm32f30x.h"
#include "config.h"
#include "debug.h"
#include "sysTick.h"
#include "outputs.h"

int main(void) {
	debugSource_t debugMain;
	int i;
	portInit();
	sysTickInit();
	debugInit();
	outputsInit();
	debugMain = debugNewSource("Main");
	debugSourceEnable(debugMain, ENABLE);
	pwmCmd(1, 254);
	pwmCmd(2, 255);
	for (;;) {
		for (i = 0; i <= PWM_MAX; i++) {
			pwmCmd(0, i);
			delayMs(3);
		}
	}
	for (;;) {
		ledCmd(0, ENABLE);
		delayMs(100);
		ledCmd(0, DISABLE);
		delayMs(900);
	}
}
