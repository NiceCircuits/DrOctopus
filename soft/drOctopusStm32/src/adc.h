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

/**
 * Read value from ADC. ADC is operated by DMA, so last converted value is
 * returned.
 * @todo Filtering of converted signals.
 * @param channel Channel used.
 * @return Last converted value from selected channel.
 */
uint16_t adcRead(uint_fast8_t channel);

#endif /* ADC_H_ */
