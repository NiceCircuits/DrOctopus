/**
 ******************************************************************************
 * @file    adc.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-15
 * @brief
 ******************************************************************************
 */

#include <stdbool.h>
#include "adc.h"
#include "config.h"
#include "outputs.h" // for pwmIrqFlag
#include "delay.h"

/// ADC conversion buffer.
static uint16_t adcBuffer[ADC_NUMBER];

uint8_t adcInit(void) {
	return adcInitVersionSpecific(adcBuffer);
}

uint8_t adcLoop(void) {
	///@todo: Maybe IRQ from DMA transfer complete will suit better?
	if (pwmIrqFlag) {
		pwmIrqFlag = false;
	}
	return 0;
}

uint16_t adcRead(uint_fast8_t channel) {
	if (channel >= ADC_NUMBER) {
		// invalid channel
		return (uint16_t) -1;
	} else {
		return adcBuffer[channel];
	}
}

#if defined(TEST_MODE) && TEST_MODE == TEST_MODE_ADC
#include "debug.h"

/// Main function for ADC test firmware
int main(void) {
	uint8_t debugAdc, i;
	FunctionalState led = DISABLE;
	defaultInit();
	debugAdc = debugNewSource("ADC");
	debugSourceEnable(debugAdc, ENABLE);
	debugPrintln(debugAdc, "test start");
	timerStartMs(100);
	for (;;) {
		adcLoop();
		if (timerEnd()) {
			timerStartMs(500);
			ledCmd(0, led);
			led = !led;
			debugPrintRaw(debugAdc, "ADC:");
			for (i = 0; i < ADC_NUMBER; i++) {
				debugPrintRaw(debugAdc, " %u", adcRead(i));
			}
			debugPrintRaw(debugAdc, "\r\n");
		}
	}
}
#endif // defined(TEST_MODE) && TEST_MODE == TEST_MODE_ADC
