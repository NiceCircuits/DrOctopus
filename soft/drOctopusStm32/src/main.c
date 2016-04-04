/**
 ******************************************************************************
 * @file    main.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-07
 * @brief   drOctopus firmware for STM32.
 * @todo Buttons.
 * @todo Self-test functions.
 * @todo BTS diagnostics.
 * @todo Logging and error handling.
 * @todo Asserts functions parameters with some kind of mechanism to signal
 *       invalid parameters outside.
 ******************************************************************************
 */

#include "config.h"
#include "debug.h"
#include "delay.h"
#include "outputs.h"
#include "servo.h"
#include "adc.h"
#include "oled.h"
#include "ESP8266.h"

debugSource_t debugMain;

#ifndef TEST_MODE
// Standard main function. TEST_MODE symbol must not be defined.
int main(void) {
	defaultInit();
	oledInit();

	debugMain = debugNewSource("Main");
	debugSourceEnable(debugMain, ENABLE);
	debugPrintln(debugMain, "Hello!");

	for (;;) {
		servoLoop();
		adcLoop();
	}
}
#endif

uint_fast8_t defaultInit() {

	portInit(); // Initialize peripheral clocks etc. Must be called before any other init.
	delayInit();
	debugInit();
	outputsInit();
	servoInit();
	adcInit();
	// OLED and I2C is not initialized here.
	//espInit();

	return 0;
}

void Default_Handler() {
	FunctionalState led = DISABLE;
	ledCmd(0, ENABLE);
	ledCmd(1, ENABLE);
	for (;;) {
		ledCmd(0, led);
		ledCmd(1, !led);
		delayMs(500);
		led = !led;
	}
}

void HardFault_Handler() {
	FunctionalState led = DISABLE;
	ledCmd(0, ENABLE);
	ledCmd(1, ENABLE);
	for (;;) {
		ledCmd(0, led);
		ledCmd(1, !led);
		delayMs(100);
		led = !led;
	}
}
