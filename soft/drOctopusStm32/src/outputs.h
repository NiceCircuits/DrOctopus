/**
  ******************************************************************************
  * @file    outputs.h
  * @author  piotr@nicecircuits.com
  * @date    2016-02-08
  * @brief   Basic outputs
  ******************************************************************************
*/
#ifndef OUTPUTS_H_
#define OUTPUTS_H_

#include <inttypes.h>
#include "config.h"
#include <stdbool.h>

/// PWM timer interrupt flag. Used to synchronize ADC processing with PWM.
extern volatile bool pwmIrqFlag;

/**
 * Initialize basic outputs - LEDs, PWMs.
 * @return 0 if OK.
 */
uint_fast8_t outputsInit(void);

/**
 * Enable or disable LED.
 * @param led Led number.
 * @param state ENABLE or DISABLE.
 * @return 0 if OK.
 */
uint_fast8_t ledCmd(uint8_t led, FunctionalState state);

/**
 * Write new PWM value.
 * @param channel logical PWM channel (0.. PWM_CHANNELS_NUMBER).
 * @param value new value (0..PWM_MAX).
 * @return 0 if OK.
 */
uint_fast8_t pwmCmd(uint8_t channel, uint16_t value);

/**
 * Setup timer as PWM on all channels.
 * @param timer pointer to timer structure.
 * @param pwmMax maximum value of PWM signal (when setting pwmCmd to pwmMax,
 * 100% duty cycle is achieved.
 * @param pwmClock frequency of PWM clock (one step).
 * @return 0 if OK.
 */
uint_fast8_t pwmTimerInit(TIM_TypeDef* timer, uint16_t pwmMax, uint32_t pwmClock);

#endif /* OUTPUTS_H_ */
