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
	FunctionalState led = ENABLE;
	int i, j;
	int_fast32_t dir, pos = 0;
	uint64_t time = 0;
	portInit();
	sysTickInit();
	debugInit();
	outputsInit();
	servoInit();

	debugMain = debugNewSource("Main");
	debugSourceEnable(debugMain, ENABLE);
	pwmCmd(0, 1);
	servoEnable(0,ENABLE);
	servoEnable(1,ENABLE);

	pos=-1000;
	for (;;) {
		servoLoop();
		if (getTime() >= time) {
			ledCmd(0, led);
			servoCmd(0, pos, 60);
			servoCmd(1, pos, 120);
			pos =-pos;
			time = getTime() + 1000;
			led = !led;
		}
	}
}
