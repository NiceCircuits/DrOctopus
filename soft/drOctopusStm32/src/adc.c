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
#include "sysTick.h"

static GPIO_TypeDef * const adcGpios[ADC_NUMBER] = ADC_GPIOS;
static uint16_t const adcPins[ADC_NUMBER] = ADC_PINS;
static uint8_t const adcChannels[] = ADC_CHANNELS;

/// ADC conversion buffer.
static uint16_t adcBuffer[ADC_NUMBER];

uint8_t adcInit(void) {
	GPIO_InitTypeDef gpio;
	ADC_InitTypeDef adc;
	DMA_InitTypeDef dma;
	uint32_t adcCalibration;
	ADC_CommonInitTypeDef adcCommon;
	uint_fast8_t i;

	// Init ADC pins.
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_AN;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	for (i = 0; i < ADC_NUMBER; i++) {
		gpio.GPIO_Pin = adcPins[i];
		GPIO_Init(adcGpios[i], &gpio);
	}

	// Init ADC DMA
	DMA_StructInit(&dma);

	dma.DMA_PeripheralBaseAddr = (uint32_t) &((ADC)->DR);
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma.DMA_MemoryBaseAddr = (uint32_t) adcBuffer;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma.DMA_BufferSize = ADC_NUMBER;
	dma.DMA_Mode = DMA_Mode_Circular;
	DMA_Init(ADC_DMA, &dma);
	DMA_Cmd(ADC_DMA, ENABLE);

	// Init ADC voltage regulator.
	ADC_VoltageRegulatorCmd(ADC, ENABLE);
	delayMs(1);

	// Calibrate ADC.
	ADC_SelectCalibrationMode(ADC, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC);
	while (ADC_GetCalibrationStatus(ADC) != RESET) {
	}
	adcCalibration = ADC_GetCalibrationValue(ADC);

	// Init ADC
	adcCommon.ADC_Mode = ADC_Mode_Independent;
	adcCommon.ADC_Clock = ADC_Clock_AsynClkMode;
	adcCommon.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	adcCommon.ADC_TwoSamplingDelay = 0;
	ADC_CommonInit(ADC, &adcCommon);

	adc.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	adc.ADC_Resolution = ADC_Resolution_12b;
	adc.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
	adc.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_OverrunMode = ADC_OverrunMode_Disable;
	adc.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	adc.ADC_NbrOfRegChannel = ADC_NUMBER;
	ADC_Init(ADC, &adc);
	ADC_DMAConfig(ADC, ADC_DMAMode_Circular);

	// Init ADC channels.
	for (i = 0; i < ADC_NUMBER; i++) {
		ADC_RegularChannelConfig(ADC, adcChannels[i], i+1,
		ADC_SampleTime_61Cycles5);
	}

	// Enable and calibrate.
	ADC_DMACmd(ADC, ENABLE);
	ADC_Cmd(ADC, ENABLE);
	//ADC_VrefintCmd(ADC, ENABLE);
	/*ADC_StartCalibration(ADC);
	 while (ADC_GetCalibrationStatus(ADC)) {
	 }*/

	// wait for ADRDY
	while (!ADC_GetFlagStatus(ADC, ADC_FLAG_RDY)) {
	}

	// Start ADC1 Software Conversion
	ADC_StartConversion(ADC);

	return 0;
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
