/**
 ******************************************************************************
 * @file    pinoutHW0.c
 * @author  piotr@nicecircuits.com
 * @date    2016-lut-07
 * @brief
 ******************************************************************************
 */

#include "config.h"

static GPIO_TypeDef * const adcGpios[ADC_NUMBER] = ADC_GPIOS;
static uint16_t const adcPins[ADC_NUMBER] = ADC_PINS;
static uint32_t const adcChannels[] = ADC_CHANNELS;

uint_fast8_t portInit(void) {
	uint16_t const pwmGpioSources[4] = { GPIO_PinSource6, GPIO_PinSource7,
	GPIO_PinSource8, GPIO_PinSource9 };
	GPIO_TypeDef * const servoGpios[SERVO_NUMBER] = SERVO_GPIOS;
	uint16_t const servoGpioSources[SERVO_NUMBER] = { GPIO_PinSource8,
	GPIO_PinSource9, GPIO_PinSource10, GPIO_PinSource11,
	GPIO_PinSource8, GPIO_PinSource7, GPIO_PinSource6, GPIO_PinSource9 };
	uint_fast16_t i;

	// ---------- GPIO clocks ----------
	// initialize all GPIO clocks (power consumption is not important).
	RCC_AHBPeriphClockCmd(
			RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN
					| RCC_AHBENR_GPIODEN | RCC_AHBENR_GPIOFEN, ENABLE);

	// ---------- Debug port ----------
	// enable debug USART and DMA peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN, ENABLE);
	// initialize USART pins alternative functions.
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource2, GPIO_AF_7);
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource3, GPIO_AF_7);

	// ---------- PWM ----------
	// enable PWM timer peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, ENABLE);
	// initialize PWM pins alternative functions.
	for (i = 0; i < 4; i++) {
		GPIO_PinAFConfig(PWM_GPIO, pwmGpioSources[i], GPIO_AF_2);
	}

	// ---------- servos ----------
	// enable servo timers peripheral clocks.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM4EN, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN, ENABLE);
	// initialize servo pins alternative functions.
	// TIM1 on GPIOA
	for (i = 0; i < 4; i++) {
		GPIO_PinAFConfig(servoGpios[i], servoGpioSources[i], GPIO_AF_6);
	}
	// TIM4 on GPIOB
	for (i = 4; i < SERVO_NUMBER; i++) {
		GPIO_PinAFConfig(servoGpios[i], servoGpioSources[i], GPIO_AF_2);
	}

	// ---------- ADC ----------
	// enable ADC peripheral clock.
	RCC_AHBPeriphClockCmd(RCC_AHBENR_ADC12EN, ENABLE);
	// set ADC clock to 12MHz
	RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div6);

	// ---------- delay ----------
	// enable delay timer peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);

	// ---------- ESP8266 ----------
	// Enable ESP USART and DMA peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART3EN, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN, ENABLE);
	// Initialize USART pins alternative functions.
	GPIO_PinAFConfig(ESP_GPIO, GPIO_PinSource10, GPIO_AF_7);
	GPIO_PinAFConfig(ESP_GPIO, GPIO_PinSource11, GPIO_AF_7);

	return 0;
}

uint_fast8_t adcInitVersionSpecific(uint16_t *adcBuffer) {
	GPIO_InitTypeDef gpio;
	ADC_InitTypeDef adc;
	DMA_InitTypeDef dma;
	uint32_t adcCalibration;
	uint_fast8_t i;
	ADC_CommonInitTypeDef adcCommon;

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

	dma.DMA_PeripheralBaseAddr = (uint32_t) &(ADC_ADC->DR);
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
	ADC_VoltageRegulatorCmd(ADC_ADC, ENABLE);
	delayMs(1);

	// Calibrate ADC.
	ADC_SelectCalibrationMode(ADC_ADC, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC_ADC);
	while (ADC_GetCalibrationStatus(ADC_ADC) != RESET) {
	}
	adcCalibration = ADC_GetCalibrationValue(ADC_ADC);

	// Init ADC
	adcCommon.ADC_Mode = ADC_Mode_Independent;
	adcCommon.ADC_Clock = ADC_Clock_AsynClkMode;
	adcCommon.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	adcCommon.ADC_TwoSamplingDelay = 0;
	ADC_CommonInit(ADC, &adcCommon);

	adc.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Disable;
	adc.ADC_Resolution = ADC_Resolution_12b;
	adc.ADC_ExternalTrigConvEvent = ADC_TRIGGER;
	adc.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_RisingEdge;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_OverrunMode = ADC_OverrunMode_Disable;
	adc.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	adc.ADC_NbrOfRegChannel = ADC_NUMBER;
	ADC_Init(ADC, &adc);
	ADC_DMAConfig(ADC, ADC_DMAMode_Circular);

	// Init ADC channels.
	for (i = 0; i < ADC_NUMBER; i++) {
		ADC_RegularChannelConfig(ADC_ADC, adcChannels[i], i + 1,
		ADC_SAMPLE_TIME);
	}

	// Enable.
	ADC_DMACmd(ADC_ADC, ENABLE);
	ADC_Cmd(ADC_ADC, ENABLE);

	// wait for ADRDY
	while (!ADC_GetFlagStatus(ADC_ADC, ADC_FLAG_RDY)) {
	}

	// Start ADC1 Software Conversion
	ADC_StartConversion(ADC_ADC);

	// Enable PWM_TIMER to be the master for ADC
	TIM_SelectOutputTrigger(PWM_TIMER, TIM_TRGOSource_Update);

	return 0;
}
