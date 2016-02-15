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
 * Initialize basic peripheral registers (mostly clocks).
 * @return 0 if OK.
 */
uint_fast8_t portInit(void);

/******************************************************************************
 * Pinout
 ******************************************************************************/
// ---------- Debug port ----------
#define DEBUG_USART USART2
#define DEBUG_GPIO GPIOA
#define DEBUG_RX_PIN GPIO_Pin_3
#define DEBUG_TX_PIN GPIO_Pin_2
#define DEBUG_DMA DMA1_Channel7

// ---------- LEDs ----------
/// Number of LEDs present.
#define LED_NUMBER 1
#define LED_GPIOS {GPIOA}
#define LED_PINS {GPIO_Pin_5}
#define LED_ACTIVE_STATES {1}

// ---------- PWM ----------
#define PWM_TIMER TIM3
#define PWM_GPIO GPIOC
// PWM channels: motor, heater, fan, fan2
#define PWM_PINS (GPIO_Pin_9 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8)
#define PWM_CHANNELS {&(TIM3->CCR4), &(TIM3->CCR1), &(TIM3->CCR2), &(TIM3->CCR3)}

// ---------- servos ----------
#define SERVO_NUMBER 8
#define SERVO_TIMERS_NUMBER 2
#define SERVO_TIMERS {TIM1, TIM4}
#define SERVO_GPIOS {GPIOA, GPIOA, GPIOA, GPIOA, GPIOB, GPIOB, GPIOB, GPIOB}
#define SERVO_PINS {GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11, GPIO_Pin_8, GPIO_Pin_7, GPIO_Pin_6, GPIO_Pin_9}
#define SERVO_CHANNELS {&(TIM1->CCR1), &(TIM1->CCR2), &(TIM1->CCR3), &(TIM1->CCR4), &(TIM4->CCR3), &(TIM4->CCR2), &(TIM4->CCR1), &(TIM4->CCR4)}
#define SERVO_IRQ TIM1_UP_TIM16_IRQn
#define SERVO_IRQ_HANDLER TIM1_UP_TIM16_IRQHandler

#endif /* PINOUTHW0_H_ */
