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

static GPIO_TypeDef * const ledGpios[LED_NUMBER] = LED_GPIOS;
static uint16_t const ledPins[LED_NUMBER] = LED_PINS;
static __IO uint32_t * const pwmChannels[] = PWM_CHANNELS;
static BitAction const ledActiveStates[LED_NUMBER] = LED_ACTIVE_STATES;

volatile bool pwmIrqFlag = false;


uint_fast8_t outputsInit(void) {
	GPIO_InitTypeDef gpio;
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
	// init PWM timer
	pwmTimerInit(PWM_TIMER, PWM_MAX, (PWM_MAX) * (PWM_FREQ));

	return 0;
}

uint_fast8_t ledCmd(uint8_t led, FunctionalState state) {
	BitAction bitState;
	bitState = !((bool) ledActiveStates[led] ^ (bool) state); // negate if active low
	if (led < LED_NUMBER) {
		GPIO_WriteBit(ledGpios[led], ledPins[led], bitState);
		return 0;
	} else {
		return 1;
	}
}

uint_fast8_t pwmCmd(uint8_t channel, uint16_t value) {
	if (channel >= (PWM_CHANNELS_NUMBER)) {
		return 1;
	}
	if (value > (PWM_MAX)) {
		// turn off pwm for safety
		*pwmChannels[channel] = 0;
		return 2;
	}
	*pwmChannels[channel] = value;
	return 0;
}

uint_fast8_t pwmTimerInit(TIM_TypeDef* timer, uint16_t pwmMax,
		uint32_t pwmClock) {
	TIM_TimeBaseInitTypeDef tim;
	TIM_OCInitTypeDef timOc;

	// init timer
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_Period = pwmMax - 1;
	tim.TIM_Prescaler = (SystemCoreClock + pwmClock / 2) / pwmClock - 1;
	TIM_TimeBaseInit(timer, &tim);

	// init output compare
	TIM_OCStructInit(&timOc);
	timOc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	timOc.TIM_OCMode = TIM_OCMode_PWM1;
	timOc.TIM_OCPolarity = TIM_OCPolarity_High;
	timOc.TIM_Pulse = 0;
	TIM_OC1Init(timer, &timOc);
	TIM_OC2Init(timer, &timOc);
	TIM_OC3Init(timer, &timOc);
	TIM_OC4Init(timer, &timOc);
	TIM_CCxCmd(timer, TIM_Channel_1, TIM_CCx_Enable);
	TIM_CCxCmd(timer, TIM_Channel_2, TIM_CCx_Enable);
	TIM_CCxCmd(timer, TIM_Channel_3, TIM_CCx_Enable);
	TIM_CCxCmd(timer, TIM_Channel_4, TIM_CCx_Enable);
	TIM_CtrlPWMOutputs(timer, ENABLE);
	TIM_Cmd(timer, ENABLE);
	return 0;
}

/**
 * PWM timer interrupt handler. Used to synchronize ADC processing with PWM.
 */
void PWM_IRQ_HANDLER(void) {
	pwmIrqFlag=true;
}
