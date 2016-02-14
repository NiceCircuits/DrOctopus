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
static uint_fast32_t servoOffset[SERVO_NUMBER];
/// Current speeds of servo movement.
static uint_fast32_t servoSpeed[SERVO_NUMBER];
/// Current positions of servos.
static uint_fast32_t servoPosition[SERVO_NUMBER];
/// Desired positions of servos.
static uint_fast32_t servoDesiredPosition[SERVO_NUMBER];
/// Servo reverse flags.
static bool servoReverse[SERVO_NUMBER];
/// Servo enable flags.
static FunctionalState servoEnabled[SERVO_NUMBER];
/// Servo busy flags.
static bool servoBusy[SERVO_NUMBER];

// ---------- private function declarations ----------

// ---------- function definitions ----------
uint_fast8_t servoInit() {
	GPIO_InitTypeDef gpio;
	uint_fast8_t i;

	gpio.GPIO_Mode = GPIO_Mode_AF;
	for (i = 0; i < SERVO_NUMBER; i++) {
		// Init servo pins.
		gpio.GPIO_Pin = servoPins[i];
		GPIO_Init(servoGpios[i], &gpio);
		// Init servo variables
		servoOffset[i] = 0;
		servoSpeed[i] = 0;
		servoPosition[i] = SERVO_ZERO;
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
	return 0;
}

uint_fast8_t servoLoop(){

}

uint_fast8_t servoCmd(uint8_t servo, int_fast32_t pos, int_fast32_t speed) {
	if (servo >= SERVO_NUMBER) {
		return 1;
	}
	if ((pos < SERVO_MIN_POS) || (pos > SERVO_MAX_POS)) {
		return 2;
	}
	*servoChannels[servo] = (uint32_t) (pos + SERVO_ZERO);
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
