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
		ledCmd(0,ENABLE);
		delayMs(100);
		ledCmd(0,DISABLE);
		delayMs(900);
	}
}
