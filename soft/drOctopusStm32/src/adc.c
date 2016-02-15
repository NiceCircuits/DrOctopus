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

uint8_t adcInit(void) {
	GPIO_InitTypeDef gpio;
	ADC_InitTypeDef adc;
	uint32_t adcCalibration;
	ADC_CommonInitTypeDef adcCommon;

	// Init ADC pins.
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &gpio);

	// Init ADC voltage regulator.
	ADC_VoltageRegulatorCmd(ADC, ENABLE);
	delayMs(1);

	// Calibrate ADC.
	ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) != RESET)
		;
	adcCalibration = ADC_GetCalibrationValue(ADC1);

	// Init ADC
	adcCommon.ADC_Mode = ADC_Mode_Independent;
	adcCommon.ADC_Clock = ADC_Clock_AsynClkMode;
	adcCommon.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	adcCommon.ADC_DMAMode = ADC_DMAMode_OneShot;
	adcCommon.ADC_TwoSamplingDelay = 0;

	ADC_CommonInit(ADC1, &adcCommon);

	adc.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	adc.ADC_Resolution = ADC_Resolution_12b;
	adc.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
	adc.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_OverrunMode = ADC_OverrunMode_Disable;
	adc.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	adc.ADC_NbrOfRegChannel = 1;
	ADC_Init(ADC1, &adc);

	// Init ADC channels.
	ADC_RegularChannelConfig(ADC, ADC_Channel_6, 1, ADC_SampleTime_61Cycles5);

	// Enable and calibrate.
	ADC_Cmd(ADC, ENABLE);
	//ADC_VrefintCmd(ADC, ENABLE);
	/*ADC_StartCalibration(ADC);
	 while (ADC_GetCalibrationStatus(ADC)) {
	 }*/

	// wait for ADRDY
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY)) {
	}

	// Start ADC1 Software Conversion
	ADC_StartConversion(ADC1);

	return 0;
}

uint8_t adcLoop(void) {
	if (pwmIrqFlag) {
		pwmIrqFlag = false;
	}
	return 0;
}
