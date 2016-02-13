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
#include "servo.h"

int main(void) {
	debugSource_t debugMain;
	int i, j, dir;
	portInit();
	sysTickInit();
	debugInit();
	outputsInit();
	servoInit();

	debugMain = debugNewSource("Main");
	debugSourceEnable(debugMain, ENABLE);
	pwmCmd(0, 1);

	dir=1;
	for (;;) {
		for (j = -1000; j <= 1000; j++) {
			for (i = 0; i < 8; i++) {
				servoCmd(i, j*dir);
			}
			delayMs(1);
		}
		dir=-dir;
	}
	for (;;) {
		ledCmd(0, ENABLE);
		delayMs(100);
		ledCmd(0, DISABLE);
		delayMs(900);
	}
}
