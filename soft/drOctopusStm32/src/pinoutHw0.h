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


#endif /* PINOUTHW0_H_ */
