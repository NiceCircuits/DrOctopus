/**
 ******************************************************************************
 * @file    pinoutHw1.h
 * @author  piotr@nicecircuits.com
 * @date    2016-02-07
 * @brief   Pinout file for HW 1
 ******************************************************************************
 */
#ifndef PINOUTHW0_H_
#define PINOUTHW0_H_

#include <inttypes.h>
#include "stm32f0xx.h"
#if defined(HW_VERSION) && HW_VERSION == HW_VERSION1
/**
 * Initialize basic peripheral registers (mostly clocks and alternative pin
 * functions).
 * @return 0 if OK.
 */
uint_fast8_t portInit(void);

/**
 * Initialize ADC - version specific function.
 * @param adcBuffer ADC DMA buffer
 * @return 0 if OK
 */
uint_fast8_t adcInitVersionSpecific(uint16_t *adcBuffer);

/******************************************************************************
 * Pinout
 ******************************************************************************/
// ---------- Debug port ----------
#define DEBUG_USART USART2
#define DEBUG_GPIO GPIOA
#define DEBUG_RX_PIN GPIO_Pin_3
#define DEBUG_TX_PIN GPIO_Pin_2
#define DEBUG_DMA DMA1_Channel4
/// Debug DMA transfer complete flag.
#define DEBUG_DMA_TC_FLAG DMA1_FLAG_TC4

// ---------- LEDs ----------
/// Number of LEDs present.
#define LED_NUMBER 2
#define LED_GPIOS {GPIOB, GPIOB}
#define LED_PINS {GPIO_Pin_12, GPIO_Pin_13}
#define LED_ACTIVE_STATES {1,1}

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
#define SERVO_TIMERS_NUMBER (4)
#define SERVO_TIMERS {TIM1, TIM15, TIM16, TIM17}
#define SERVO_GPIOS {GPIOA, GPIOA, GPIOA, GPIOA, GPIOB, GPIOB, GPIOB, GPIOB}
#define SERVO_PINS {GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10, GPIO_Pin_11, GPIO_Pin_8, GPIO_Pin_15, GPIO_Pin_14, GPIO_Pin_9}
#define SERVO_CHANNELS {&(TIM1->CCR1), &(TIM1->CCR2), &(TIM1->CCR3), &(TIM1->CCR4), &(TIM16->CCR1), &(TIM15->CCR2), &(TIM15->CCR1), &(TIM17->CCR1)}
#define SERVO_IRQ TIM1_BRK_UP_TRG_COM_IRQn
#define SERVO_IRQ_HANDLER TIM1_BRK_UP_TRG_COM_IRQHandler

// ---------- ADC ----------
#define ADC_ADC ADC1
/// Number of ADC channels.
#define ADC_NUMBER (8)
// ADC channels: heater_sig, bts_fb_sig, thermistors from 0
#define ADC_GPIOS {GPIOA, GPIOC, GPIOA, GPIOA, GPIOC, GPIOC, GPIOC, GPIOC}
#define ADC_PINS {GPIO_Pin_5, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7, GPIO_Pin_4, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3}
#define ADC_CHANNELS {ADC_Channel_5, ADC_Channel_15, ADC_Channel_6, ADC_Channel_7, ADC_Channel_14, ADC_Channel_11, ADC_Channel_12, ADC_Channel_13}
#define ADC_DMA DMA1_Channel1
/// ADC conversion trigger event: Timer 3
#define ADC_TRIGGER (ADC_ExternalTrigConv_T3_TRGO)
#define ADC_FLAG_RDY ADC_FLAG_ADRDY
#define ADC_SAMPLE_TIME ADC_SampleTime_55_5Cycles

// ---------- I2C ----------
#define I2C I2C2
// I2C pins: SDA, SCL
#define I2C_GPIOS {GPIOB, GPIOB}
#define I2C_PINS {GPIO_Pin_11, GPIO_Pin_10}

// ---------- delay ----------
#define DELAY_TIMER TIM2

// ---------- ESP8266 ----------
#define ESP_USART USART3
#define ESP_GPIO GPIOC
#define ESP_RX_PIN GPIO_Pin_11
#define ESP_TX_PIN GPIO_Pin_10
#define ESP_EN_GPIO GPIOB
#define ESP_EN_PIN GPIO_Pin_1
#define ESP_BOOT_GPIO GPIOB
#define ESP_BOOT_PIN GPIO_Pin_0
#define ESP_TX_DMA DMA1_Channel2
/// ESP8266 DMA transmit complete flag.
#define ESP_DMA_TX_TC_FLAG DMA1_FLAG_TC2
#define ESP_IRQHandler USART3_6_IRQHandler
#define ESP_IRQ USART3_6_IRQn
#else // #if defined(HW_VERSION) && HW_VERSION == HW_VERSION1
#error "Invalid pinout file used or HW version not defined!"
#endif
#endif /* PINOUTHW0_H_ */
