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
	portInit();
	sysTickInit();
	debugInit();
	outputsInit();
	for (;;) {
		ledCmd(0, ENABLE);
		delayMs(100);
		ledCmd(0, DISABLE);
		delayMs(900);
		debugPrint(0, "DMA test.\r\n");
		delayMs(100);
		debugPrint(0, "a=%d\r\n", 100);
		delayMs(100);
		debugPrint(0, "b=%s\r\n", "xxx");
		delayMs(100);
		debugPrint(0, "c=%1.3f\r\nd=0x%x\r\n", 3.14159, 12345);
	}
}
