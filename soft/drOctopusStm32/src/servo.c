/**
 ******************************************************************************
 * @file    servo.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-13
 * @brief
 ******************************************************************************
 */

#include <inttypes.h>
#include "outputs.h"
#include "config.h"

GPIO_TypeDef * const servoGpios[SERVO_NUMBER] = SERVO_GPIOS;
static uint16_t const servoPins[SERVO_NUMBER] = SERVO_PINS;
TIM_TypeDef* const servoTimers[SERVO_TIMERS_NUMBER] = SERVO_TIMERS;
static __IO uint32_t * const servoChannels[SERVO_NUMBER] = SERVO_CHANNELS;

const uint32_t SERVO_FREQ = 50;
/// counts per millisecond
#define SERVO_MS (2000)
const int_fast32_t SERVO_MIN_POS = -SERVO_MS;
const int_fast32_t SERVO_MAX_POS = SERVO_MS;
const int_fast32_t SERVO_ZERO = SERVO_MS * 3 / 2;
const int_fast32_t SERVO_PWM_MAX = SERVO_MS * 20;

uint_fast8_t servoInit() {
	GPIO_InitTypeDef gpio;
	uint_fast8_t i;

	// Init servo pins.
	gpio.GPIO_Mode = GPIO_Mode_AF;
	for (i = 0; i < SERVO_NUMBER; i++) {
		gpio.GPIO_Pin = servoPins[i];
		GPIO_Init(servoGpios[i], &gpio);
	}

	// Init servo timers.
	for (i = 0; i < SERVO_TIMERS_NUMBER; i++) {
		pwmTimerInit(servoTimers[i], SERVO_PWM_MAX, (SERVO_PWM_MAX) * (SERVO_FREQ));
	}
	return 0;
}

uint_fast8_t servoCmd(uint8_t servo, int_fast32_t pos) {
	if (servo >= SERVO_NUMBER) {
		return 1;
	}
	if ((pos < SERVO_MIN_POS) || (pos > SERVO_MAX_POS)) {
		return 2;
	}
	*servoChannels[servo] = (uint32_t)(pos + SERVO_ZERO);
	return 0;
}
