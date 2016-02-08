/**
 ******************************************************************************
 * @file    pinoutHw0.h
 * @author  piotr@nicecircuits.com
 * @date    2016-02-07
 * @brief   Pinout file for HW 0 (NUCLEO-F303RE)
 ******************************************************************************
 */
#ifndef PINOUTHW0_H_
#define PINOUTHW0_H_

#include <inttypes.h>
#include "stm32f30x.h"

/**
 * Initialize basic port registers (clocks). All other port registers
 * (direction, initial state etc.) should be initialized in functions using
 * these port pins.
 * @return 0 if OK.
 */
uint8_t portInit(void);

/******************************************************************************
 * Pinout
 ******************************************************************************/
// ---------- Debug port ----------
#define DEBUG_USART USART2
#define DEBUG_GPIO GPIOA
#define DEBUG_RX_PIN GPIO_Pin_3
#define DEBUG_TX_PIN GPIO_Pin_2
#define DEBUG_DMA DMA1_Channel7
/**
 * Initialize peripheral clock for debug USART
 * @return 0 if OK.
 */
uint8_t debugClockEnable(void);
/**
 * Setup alternate functions of GPIO for debug USART
 * @return 0 if OK.
 */
uint8_t debugGpioAfSetup(void);

// ---------- LEDs ----------
/// Number of LEDs present.
#define LED_NUMBER 1
#define LED_GPIOS {GPIOA}
#define LED_PINS {GPIO_Pin_5}
#define LED_ACTIVE_STATES {1}

#endif /* PINOUTHW0_H_ */
