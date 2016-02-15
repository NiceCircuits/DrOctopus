/**
  ******************************************************************************
  * @file    sysTick.h
  * @author  piotr@nicecircuits.com
  * @date    2016-02-08
  * @brief   System clock functions
  ******************************************************************************
*/
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <inttypes.h>

/**
 * Initialize SysTick to generate exception every 1ms
 * @return 0 if OK
 */
uint_fast8_t sysTickInit(void);

/**
 * Delay for some ms.
 * @param time Time in ms.
 * @return 0 if OK
 */
uint_fast8_t delayMs(uint32_t time);

/**
 * Get time from start.
 * @return Time from start in ms.
 */
uint64_t getTime();

#endif /* SYSTICK_H_ */
