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
#include "stm32f30x.h"

/**
 * Initialize basic outputs
 * @return 0 if OK
 */
uint8_t outputsInit(void);

/**
 * Enable or disable LED
 * @param led Led number
 * @param state ENABLE or DISABLE
 * @return 0 if OK
 */
uint8_t ledCmd(uint8_t led, FunctionalState state);

/**
 * Write new PWM value
 * @param channel logical PWM channel (0.. PWM_CHANNELS_NUMBER)
 * @param value new value (0..PWM_MAX)
 * @return 0 if OK
 */
uint8_t pwmCmd(uint8_t channel, uint16_t value);

#endif /* OUTPUTS_H_ */
