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
static uint8_t const adcChannels[] = ADC_CHANNELS;

uint_fast8_t portInit(void) {
	uint16_t const pwmGpioSources[4] = { GPIO_PinSource9, GPIO_PinSource6,
	GPIO_PinSource7, GPIO_PinSource8 };
	GPIO_TypeDef * const servoGpios[SERVO_NUMBER] = SERVO_GPIOS;
	uint16_t const servoGpioSources[SERVO_NUMBER] = { GPIO_PinSource8,
	GPIO_PinSource9, GPIO_PinSource10, GPIO_PinSource11,
	GPIO_PinSource8, GPIO_PinSource15, GPIO_PinSource14, GPIO_PinSource9 };
	uint_fast16_t i;

	// ---------- GPIO clocks ----------
	// initialize all GPIO clocks (power consumption is not important).
	RCC_AHBPeriphClockCmd(
			RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN
					| RCC_AHBENR_GPIODEN, ENABLE);

	// ---------- Debug port ----------
	// enable debug USART and DMA peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN, ENABLE);
	// initialize USART pins alternative functions.
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource3, GPIO_AF_1);

	// ---------- PWM ----------
	// enable PWM timer peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, ENABLE);
	// initialize PWM pins alternative functions.
	for (i = 0; i < 4; i++) {
		GPIO_PinAFConfig(PWM_GPIO, pwmGpioSources[i], GPIO_AF_1);
	}

	// ---------- servos ----------
	// enable servo timers peripheral clocks.
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1EN, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM15EN, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM16EN, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM17EN, ENABLE);
	// initialize servo pins alternative functions.
	// TIM1 on GPIOA
	for (i = 0; i < 4; i++) {
		GPIO_PinAFConfig(servoGpios[i], servoGpioSources[i], GPIO_AF_2);
	}
	GPIO_PinAFConfig(servoGpios[4], servoGpioSources[4], GPIO_AF_2);
	GPIO_PinAFConfig(servoGpios[5], servoGpioSources[5], GPIO_AF_1);
	GPIO_PinAFConfig(servoGpios[6], servoGpioSources[6], GPIO_AF_1);
	GPIO_PinAFConfig(servoGpios[7], servoGpioSources[7], GPIO_AF_2);

	// ---------- ADC ----------
	// enable ADC peripheral clock.
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADCEN, ENABLE);
	// set ADC clock to 12MHz
	RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div4);

	// ---------- delay ----------
	// enable delay timer peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2EN, ENABLE);

	// ---------- ESP8266 ----------
	// Enable ESP USART and DMA peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART3EN, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN, ENABLE);
	// Initialize USART pins alternative functions.
	GPIO_PinAFConfig(ESP_GPIO, GPIO_PinSource10, GPIO_AF_1);
	GPIO_PinAFConfig(ESP_GPIO, GPIO_PinSource11, GPIO_AF_1);

	return 0;
}

uint_fast8_t adcInitVersionSpecific(uint16_t *adcBuffer) {
	GPIO_InitTypeDef gpio;
	ADC_InitTypeDef adc;
	DMA_InitTypeDef dma;
	uint32_t adcCalibration;
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

	// Calibrate ADC.
	adcCalibration = ADC_GetCalibrationFactor(ADC_ADC);

	// Init ADC
	adc.ADC_ContinuousConvMode = DISABLE;
	adc.ADC_Resolution = ADC_Resolution_12b;
	adc.ADC_ExternalTrigConv = ADC_TRIGGER;
	adc.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_Init(ADC, &adc);
	ADC_DMARequestModeConfig(ADC, ADC_DMAMode_Circular);

	// Init ADC channels.
	for (i = 0; i < ADC_NUMBER; i++) {
		ADC_ChannelConfig(ADC_ADC, adcChannels[i], ADC_SAMPLE_TIME);
	}

	// Enable.
	ADC_DMACmd(ADC_ADC, ENABLE);
	ADC_Cmd(ADC_ADC, ENABLE);

	// wait for ADRDY
	while (!ADC_GetFlagStatus(ADC_ADC, ADC_FLAG_RDY)) {
	}

	// Start ADC1 Software Conversion
	ADC_StartOfConversion(ADC_ADC);

	// Enable PWM_TIMER to be the master for ADC
	TIM_SelectOutputTrigger(PWM_TIMER, TIM_TRGOSource_Update);

	return 0;
}
