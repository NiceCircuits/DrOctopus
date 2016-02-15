/**
  ******************************************************************************
  * @file    adc.h
  * @author  piotr@nicecircuits.com
  * @date    2016-02-15
  * @brief   
  ******************************************************************************
*/
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

/**
 * Initialize ADC.
 * @return 0 if OK.
 */
uint8_t adcInit(void);

/**
 * ADC loop.
 * @return 0 if OK.
 */
uint8_t adcLoop(void);

#endif /* ADC_H_ */
