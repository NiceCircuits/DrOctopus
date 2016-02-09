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
	debugSource_t debugMain, test;
	portInit();
	sysTickInit();
	debugInit();
	outputsInit();
	debugMain = debugNewSource("Main");
	test=debugNewSource("test");
	debugSourceSetEnabled(test,ENABLE);
	debugPrintln(test,"aaaa");
	debugPrintln(debugMain, "DMA test.");
	delayMs(100);
	debugPrintln(debugMain, "a=%d", 100);
	delayMs(100);
	debugSourceSetEnabled(debugMain, ENABLE);
	debugPrintln(debugMain, "b=%s", "xxx");
	delayMs(100);
	debugPrintln(debugMain, "c=%1.3f\r\nd=0x%x", 3.14159, 12345);
	for (;;) {
		ledCmd(0, ENABLE);
		delayMs(100);
		ledCmd(0, DISABLE);
		delayMs(900);
	}
}
