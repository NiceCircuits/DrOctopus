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
#define TEST_MODE_I2C 2
#define TEST_MODE_OLED 3

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
enum {
	/// Debug port baudrate.
	DEBUG_BUADRATE = 115200,
	/// Debug transmit buffer size.
	DEBUG_BUFFER_SIZE = 512
};

// ---------- PWM outputs ----------
enum {
	PWM_CHANNELS_NUMBER = 4, PWM_FREQ = 1000, PWM_MAX = 255,
// PWM logical channels (not equal physical timer channels)
	PWM_MOTOR_CHANNEL = 0,
	PWM_HEATER_CHANNEL,
	PWM_FAN1_CHANNEL,
	PWM_FAN2_CHANNEL
};

// ---------- ADC inputs ----------
/// ADC logical channels (not equal physical channels)
enum {
	ADC_HEATER_SIGNAL = 0, ADC_BTS_FEEDBACK = 1,
/// First thermistor channel, the rest of thermistor channels follows.
	ADC_THERM_SIGNAL0 = 2,
	ADC_THERM_SIGNAL1,
	ADC_THERM_SIGNAL2,
	ADC_THERM_SIGNAL3,
	ADC_THERM_SIGNAL4,
	ADC_THERM_SIGNAL5,
	ADC_THERM_SIGNAL6
};

// ---------- I2C ----------
enum {
	I2C_TIMEOUT_US = 2000
};

// ---------- OLED ----------
enum {
	OLED_I2C_ADDR = 0x3C
};
#endif /* CONFIG_H_ */
