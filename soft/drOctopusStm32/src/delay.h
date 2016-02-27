/**
 ******************************************************************************
 * @file    sysTick.h
 * @author  piotr@nicecircuits.com
 * @date    2016-02-08
 * @brief   Delay functions.
 ******************************************************************************
 */
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <inttypes.h>

/**
 * Initialize SysTick and delay timer.
 * @return 0 if OK
 */
uint_fast8_t delayInit(void);

/**
 * Delay for some ms.
 * @param time Time in ms.
 * @return 0 if OK
 */
uint_fast8_t delayMs(uint16_t time);

/**
 * Delay for some us. If delay time is >=1000us, delay is rounded to 1ms.
 * @param time Time in us.
 * @return 0 if OK, 1 if delay rounded.
 */
uint_fast8_t delayUs(uint16_t time);

/**
 * Start timer with delay stated in us.
 * @param time Time in us.
 * @return 0 if OK.
 */
uint_fast8_t timerStartUs(uint16_t time);

/**
 * Start timer with delay stated in ms.
 * @param time Time in ms.
 * @return 0 if OK.
 */
uint_fast8_t timerStartMs(uint16_t time);

/**
 * Check, if delay timer stopped counting.
 * @return 1 if timer stopped counting.
 */
uint_fast8_t timerEnd(void);

/**
 * Get time from start.
 * @return Time from start in ms.
 */
uint64_t getTime();

#endif /* SYSTICK_H_ */
