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

#include <inttypes.h>

// ---------- Test modes ----------
/*
 * Used to build test firmwares for different functions. If TEST_MODE symbol
 * is defined in build configuration and has any of the following values, test
 * firmware is build instead of normal one.
 */

#define TEST_MODE_DELAY 1
#define TEST_MODE_I2C 2
#define TEST_MODE_OLED 3
#define TEST_MODE_DEBUG 4
#define TEST_MODE_ESP 5
#define TEST_MODE_ADC 6
#define TEST_MODE_SERVO 7
#define TEST_MODE_OUTPUTS 8

/**
 * Default init function. Defined in main.c. Excluded from main, can be used in
 * main functions in test modes.
 * @return 0 if OK.
 */
uint_fast8_t defaultInit();

// ---------- Pinout and HW versions ----------
/// Hardware version 0 - NUCLEO-F303RE. Used until PCB is ready.
#define HW_VERSION0 0
/// Hardware version 1 - PCB v2.0 with STM32F030RCT6
#define HW_VERSION1 1

/// Define used HW version
#define HW_VERSION HW_VERSION1

// include pinout file for used hardware
#if HW_VERSION == HW_VERSION0
#include "pinoutHw0.h"
#elif HW_VERSION == HW_VERSION1
#include "pinoutHw1.h"
#else
#error "Other hardware not supported."
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
	PWM_CHANNELS_NUMBER = 4, PWM_FREQ = 200, PWM_MAX = 255,
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
	/// I2C frequency in Hz.
	I2C_FREQ = 100000,
	/// I2C single bit time in us, calculated. Rounded up.
	I2C_BIT_TIME_US = (1000000 + I2C_FREQ - 1) / I2C_FREQ
};

// ---------- OLED ----------
enum {
	OLED_I2C_ADDR = 0x3C
};

// ---------- ESP8266 ----------
enum {
	/// ESP8266 port baudrate.
	ESP_BUADRATE=115200,
	/// ESP8266 transmit buffer size.
	ESP_TX_BUFFER_SIZE = 512,
	/// ESP8266 transmit buffer size.
	ESP_RX_BUFFER_SIZE = 512
};
#endif /* CONFIG_H_ */
