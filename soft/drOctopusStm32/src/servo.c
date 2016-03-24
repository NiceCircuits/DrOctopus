/**
 ******************************************************************************
 * @file    servo.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-13
 * @brief
 ******************************************************************************
 */

#include <inttypes.h>
#include <stdbool.h>
#include "outputs.h"
#include "config.h"

// ---------- constants ----------
/// Servo pulse frequency.
const uint32_t SERVO_FREQ = 50;
/// Counts per millisecond.
#define SERVO_MS (2000)
/// Minimum position value.
const int_fast32_t SERVO_MIN_POS = -SERVO_MS;
/// Maximum position value.
const int_fast32_t SERVO_MAX_POS = SERVO_MS;
/// Zero position value.
const int_fast32_t SERVO_ZERO = SERVO_MS * 3 / 2;
/// Maximum value of servo counter
const int_fast32_t SERVO_CNT_MAX = SERVO_MS * 20;

// ---------- pinout arrays ----------
GPIO_TypeDef * const servoGpios[SERVO_NUMBER] = SERVO_GPIOS;
static uint16_t const servoPins[SERVO_NUMBER] = SERVO_PINS;
TIM_TypeDef* const servoTimers[SERVO_TIMERS_NUMBER] = SERVO_TIMERS;
static __IO uint32_t * const servoChannels[SERVO_NUMBER] = SERVO_CHANNELS;

// ---------- private variables ----------
/// Offsets of servos to trim zero position.
static int_fast32_t servoOffset[SERVO_NUMBER];
/// Current speeds of servo movement.
static uint_fast32_t servoSpeed[SERVO_NUMBER];
/// Current positions of servos.
static int_fast32_t servoPosition[SERVO_NUMBER];
/// Desired positions of servos.
static int_fast32_t servoDesiredPosition[SERVO_NUMBER];
/// Servo reverse flags.
static bool servoReverse[SERVO_NUMBER];
/// Servo enable flags.
static FunctionalState servoEnabled[SERVO_NUMBER];
/// Servo busy flags.
static bool servoBusy[SERVO_NUMBER];
/// Servo interrupt flag
static volatile bool servoIrqFlag = false;

// ---------- private function declarations ----------

// ---------- function definitions ----------
uint_fast8_t servoInit() {
	GPIO_InitTypeDef gpio;
	NVIC_InitTypeDef nvic;
	uint_fast8_t i;

	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	for (i = 0; i < SERVO_NUMBER; i++) {
		// Init servo pins.
		gpio.GPIO_Pin = servoPins[i];
		GPIO_Init(servoGpios[i], &gpio);
		// Init servo variables
		servoOffset[i] = 0;
		servoSpeed[i] = 0;
		servoPosition[i] = 0;
		servoDesiredPosition[i] = 0;
		servoReverse[i] = false;
		servoEnabled[i] = false;
		servoBusy[i] = false;
	}

	// Init servo timers.
	for (i = 0; i < SERVO_TIMERS_NUMBER; i++) {
		pwmTimerInit(servoTimers[i], SERVO_CNT_MAX,
				(SERVO_CNT_MAX) * (SERVO_FREQ));
	}

	// Init servo timer update interrupt
	nvic.NVIC_IRQChannel = (SERVO_IRQ);
	nvic.NVIC_IRQChannelPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	TIM_ITConfig(servoTimers[0], TIM_IT_Update, ENABLE);
	return 0;
}

uint_fast8_t servoLoop() {
	uint_fast8_t servo;
	int_fast32_t position, desired;
	int_fast32_t speed;
	if (servoIrqFlag) {
		servoIrqFlag = false;
		for (servo = 0; servo < SERVO_NUMBER; servo++) {
			if (servoEnabled[servo]) {
				position = servoPosition[servo];
				desired = servoDesiredPosition[servo];
				speed = servoSpeed[servo];
				if (position == desired) {
					// do nothing
				} else if (position + speed < desired) {
					// limit speed
					position += speed;
				} else if (position - speed > desired) {
					// limit speed
					position -= speed;
				} else {
					// go to desired position
					position = desired;
				}
				// save new position
				servoPosition[servo] = position;
				// calculate pulse length
				if (servoReverse[servo]) {
					position = -position;
				}
				*servoChannels[servo] = (uint32_t) (position + SERVO_ZERO
						+ servoOffset[servo]);
			} else {
				// servo disabled, do not generate pulse
				*servoChannels[servo] = 0;
			}
		}
		servoIrqFlag = false;
	}
	return 0;
}

uint_fast8_t servoCmd(uint8_t servo, int_fast32_t pos, uint_fast32_t speed) {
	if (servo >= SERVO_NUMBER) {
		return 1;
	}
	if ((pos < SERVO_MIN_POS) || (pos > SERVO_MAX_POS)) {
		return 2;
	}
	servoDesiredPosition[servo] = pos;
	servoSpeed[servo] = speed;
	return 0;
}

uint_fast8_t servoEnable(uint8_t servo, FunctionalState enabled) {
	if (servo >= SERVO_NUMBER) {
		return 1;
	}
	if (!IS_FUNCTIONAL_STATE(enabled)) {
		return 2;
	}
	servoEnabled[servo] = enabled;

	return 0;
}

void SERVO_IRQ_HANDLER() {
	if (TIM_GetITStatus(servoTimers[0], TIM_IT_Update) == SET) {
		TIM_ClearITPendingBit(servoTimers[0], TIM_IT_Update);
		servoIrqFlag = true;
	}
}
