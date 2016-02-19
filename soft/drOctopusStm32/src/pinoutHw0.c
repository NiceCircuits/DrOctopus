/**
 ******************************************************************************
 * @file    pinoutHW0.c
 * @author  piotr@nicecircuits.com
 * @date    2016-lut-07
 * @brief
 ******************************************************************************
 */

#include "pinoutHw0.h"

uint_fast8_t portInit(void) {
	uint16_t const pwmGpioSources[4] = { GPIO_PinSource6, GPIO_PinSource7,
	GPIO_PinSource8, GPIO_PinSource9 };
	GPIO_TypeDef * const servoGpios[SERVO_NUMBER] = SERVO_GPIOS;
	uint16_t const servoGpioSources[SERVO_NUMBER] = { GPIO_PinSource8,
	GPIO_PinSource9, GPIO_PinSource10, GPIO_PinSource11,
	GPIO_PinSource8, GPIO_PinSource7, GPIO_PinSource6, GPIO_PinSource9 };
	uint_fast16_t i;

	// initialize all GPIO clocks (power consumption is not important).
	RCC_AHBPeriphClockCmd(
			RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN
					| RCC_AHBENR_GPIODEN | RCC_AHBENR_GPIOFEN, ENABLE);

	// enable debug USART and DMA peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN, ENABLE);
	// initialize USART pins alternative functions.
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource2, GPIO_AF_7);
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource3, GPIO_AF_7);

	// enable PWM timer peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, ENABLE);
	// initialize PWM pins alternative functions.
	for (i = 0; i < 4; i++) {
		GPIO_PinAFConfig(PWM_GPIO, pwmGpioSources[i], GPIO_AF_2);
	}

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

	// enable ADC peripheral clock.
	RCC_AHBPeriphClockCmd(RCC_AHBENR_ADC12EN, ENABLE);
	// set ADC clock to 12MHz
	RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div6);

	// Enable I2C peripheral clock.
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	// Set I2C clock to internal clock 8MHz.
	RCC_I2CCLKConfig(RCC_I2C1CLK_HSI);
	// initialize I2C pins alternative functions.
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_4);
	return 0;
}
