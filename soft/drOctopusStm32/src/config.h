/**
 ******************************************************************************
 * @file    config.h
 * @author  piotr@nicecircuits.com
 * @date    2016-02-07
 * @brief   Configuration file for device
 ******************************************************************************
 */

#ifndef CONFIG_H_
#define CONFIG_H_
// ---------- Test modes ----------
/*
 * Used to build test firmwares for different functions. If TEST_MODE symbol
 * is defined in build configuration and has any of the following values, test
 * firmware is build instead of normal one.
 */

#define TEST_MODE_DELAY 1

/**
 * Default init function. Defined in main.c. Excluded from main, can be used in
 * main functions in test modes.
 * @return 0 if OK.
 */
uint_fast8_t defaultInit();

// ---------- Pinout and HW versions ----------
/// Hardware version 0 - NUCLEO-F303RE. Used until PCB is ready.
#define HW_VERSION0 0
/// Hardware version 1 - PCB v2.0 with STM32F103RBT6
#define HW_VERSION1 1

/// Define used HW version
#define HW_VERSION HW_VERSION0

// include pinout file for used hardware
#if HW_VERSION == HW_VERSION0
#include "pinoutHw0.h"
#else
#error "Other hardware not supported yet."
#endif

// ---------- Debug port ----------
#define DEBUG_BUADRATE (115200)
#define DEBUG_BUFFER_SIZE (512)

// ---------- PWM outputs ----------
#define PWM_CHANNELS_NUMBER (4)
#define PWM_FREQ (1000)
#define PWM_MAX (255)
// PWM logical channels (not equal physical timer channels)
#define PWM_MOTOR_CHANNEL (0)
#define PWM_HEATER_CHANNEL (1)
#define PWM_FAN1_CHANNEL (2)
#define PWM_FAN2_CHANNEL (3)

// ---------- ADC inputs ----------
// ADC logical channels (not equal physical channels)
#define ADC_HEATER_SIGNAL (0)
#define ADC_BTS_FEEDBACK (1)
/// First thermistor channel, the rest of thermistor channels follows.
#define ADC_THERM_SIGNAL (2)

// ---------- I2C ----------
#define I2C_BITRATE (100000)
#endif /* CONFIG_H_ */
