/**
  ******************************************************************************
  * @file    i2c.h
  * @author  piotr@nicecircuits.com
  * @date    2016-02-17
  * @brief   
  ******************************************************************************
*/
#ifndef I2C_H_
#define I2C_H_

#include <inttypes.h>

/**
 * Initialize I2C.
 * @return 0 if OK.
 */
uint_fast8_t i2cInit(void);

#endif /* I2C_H_ */
