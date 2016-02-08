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

#endif /* OUTPUTS_H_ */
