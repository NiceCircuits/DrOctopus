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
#include "stm32f0xx.h"

/**
 * Initialize basic peripheral registers (mostly clocks and alternative pin
 * functions).
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
/// Debug DMA transfer complete flag.
#define DEBUG_DMA_TC_FLAG DMA1_FLAG_TC7

// ---------- LEDs ----------
/// Number of LEDs present.
#define LED_NUMBER 3
#define LED_GPIOS {GPIOA, GPIOB, GPIOB}
#define LED_PINS {GPIO_Pin_5, GPIO_Pin_13, GPIO_Pin_14}
#define LED_ACTIVE_STATES {1,1,1}

// ---------- PWM ----------
#define PWM_TIMER TIM3
#define PWM_GPIO GPIOC
// PWM channels: motor, heater, fan, fan2
#define PWM_PINS (GPIO_Pin_9 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8)
#define PWM_CHANNELS {&(TIM3->CCR4), &(TIM3->CCR1), &(TIM3->CCR2), &(TIM3->CCR3)}
#define PWM_IRQ TIM3_IRQn
#define PWM_IRQ_HANDLER TIM3_IRQHandler

// ---------- servos ----------
#define SERVO_NUMBER (8)
#define SERVO_TIMERS_NUMBER (2)
#define SERVO_TIMERS {TIM1, TIM4}
#define SERVO_GPIOS {GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOB, GPIOB}
#define SERVO_PINS {GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11, GPIO_Pin_13, GPIO_Pin_12, GPIO_Pin_6, GPIO_Pin_9}
#define SERVO_CHANNELS {&(TIM1->CCR1), &(TIM1->CCR2), &(TIM1->CCR3), &(TIM1->CCR4), &(TIM4->CCR3), &(TIM4->CCR2), &(TIM4->CCR1), &(TIM4->CCR4)}
#define SERVO_IRQ TIM1_UP_TIM16_IRQn
#define SERVO_IRQ_HANDLER TIM1_UP_TIM16_IRQHandler

// ---------- ADC ----------
#define ADC ADC1
/// Number of ADC channels.
#define ADC_NUMBER (7)
// ADC channels: heater_sig, bts_fb_sig, thermistors from 0
#define ADC_GPIOS {GPIOC, GPIOA, GPIOB, GPIOC, GPIOA, GPIOC, GPIOC}
#define ADC_PINS {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_11, GPIO_Pin_3, GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2}
#define ADC_CHANNELS {ADC_Channel_6, ADC_Channel_2, ADC_Channel_14, ADC_Channel_9, ADC_Channel_1, ADC_Channel_7, ADC_Channel_8}
#define ADC_DMA DMA1_Channel1
/// ADC conversion trigger event: Timer 3
#define ADC_TRIGGER (ADC_ExternalTrigConvEvent_4)

// ---------- I2C ----------
#define I2C I2C1
// I2C pins: SDA, SCL
#define I2C_GPIOS {GPIOB, GPIOB}
#define I2C_PINS {GPIO_Pin_7, GPIO_Pin_8}

// ---------- delay ----------
#define DELAY_TIMER TIM2

// ---------- ESP8266 ----------
#define ESP_USART USART3
#define ESP_GPIO GPIOC
#define ESP_RX_PIN GPIO_Pin_11
#define ESP_TX_PIN GPIO_Pin_10
#define ESP_RX_DMA DMA1_Channel3
#define ESP_TX_DMA DMA1_Channel2
/// ESP8266 DMA transmit complete flag.
#define ESP_DMA_TX_TC_FLAG DMA1_FLAG_TC2
#define ESP_IRQHandler USART3_IRQHandler
#define ESP_IRQ USART3_IRQn

#endif /* PINOUTHW0_H_ */
