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

#endif /* CONFIG_H_ */
