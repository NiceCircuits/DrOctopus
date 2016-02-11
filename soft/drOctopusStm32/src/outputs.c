/**
 ******************************************************************************
 * @file    outputs.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-08
 * @brief   Basic outputs
 ******************************************************************************
 */

#include "outputs.h"
#include "config.h"
#include <stdbool.h>

GPIO_TypeDef * const ledGpios[LED_NUMBER] = LED_GPIOS;
static uint16_t const ledPins[LED_NUMBER] = LED_PINS;
static BitAction const ledActiveStates[LED_NUMBER] = LED_ACTIVE_STATES;

static __IO uint32_t * const pwmChannels[] = PWM_CHANNELS;

uint8_t outputsInit(void) {
	GPIO_InitTypeDef gpio;
	TIM_TimeBaseInitTypeDef tim;
	TIM_OCInitTypeDef timOc;
	uint_fast8_t i;

	// LED pins - low speed outputs
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	for (i = 0; i < (LED_NUMBER); i++) {
		gpio.GPIO_Pin = ledPins[i];
		GPIO_Init(ledGpios[i], &gpio);
	}

	// PWM pins
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_Pin = (PWM_PINS);
	GPIO_Init(PWM_GPIO, &gpio);
	// PWM Timer init
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = (PWM_MAX) - 1;
	tim.TIM_Prescaler = (SystemCoreClock + ((PWM_MAX) * (PWM_FREQ)) / 2)
			/ ((PWM_MAX) * (PWM_FREQ))-1; // coreClock/PwmStepTime + 0.5 to round
	TIM_TimeBaseInit(PWM_TIMER, &tim);
	// PWM output compare init
	TIM_OCStructInit(&timOc);
	timOc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	timOc.TIM_OCMode = TIM_OCMode_PWM1;
	timOc.TIM_OCPolarity = TIM_OCPolarity_High;
	timOc.TIM_Pulse = 0;
	TIM_OC1Init(PWM_TIMER, &timOc);
	TIM_OC2Init(PWM_TIMER, &timOc);
	TIM_OC3Init(PWM_TIMER, &timOc);
	TIM_OC4Init(PWM_TIMER, &timOc);
	TIM_CCxCmd(PWM_TIMER, TIM_Channel_1, TIM_CCx_Enable);
	TIM_CCxCmd(PWM_TIMER, TIM_Channel_2, TIM_CCx_Enable);
	TIM_CCxCmd(PWM_TIMER, TIM_Channel_3, TIM_CCx_Enable);
	TIM_CCxCmd(PWM_TIMER, TIM_Channel_4, TIM_CCx_Enable);
	TIM_CtrlPWMOutputs(PWM_TIMER, ENABLE);
	TIM_Cmd(PWM_TIMER, ENABLE);

	return 0;
}

uint8_t ledCmd(uint8_t led, FunctionalState state) {
	BitAction bitState;
	bitState = !((bool) ledActiveStates[led] ^ (bool) state); // negate if active low
	if (led < LED_NUMBER) {
		GPIO_WriteBit(ledGpios[led], ledPins[led], bitState);
		return 0;
	} else {
		return 1;
	}
}

uint8_t pwmCmd(uint8_t channel, uint16_t value) {
	if (channel >= (PWM_CHANNELS_NUMBER)) {
		return 1;
	}
	if (value > (PWM_MAX)) {
		return 2;
	}
	*pwmChannels[channel] = value;
	return 0;
}
