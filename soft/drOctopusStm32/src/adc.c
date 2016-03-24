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
	if (pwmIrqFlag) {
		pwmIrqFlag = false;
	}
	return 0;
}

uint16_t adcRead(uint_fast8_t channel) {
	return adcBuffer[channel];
}

///@todo test
