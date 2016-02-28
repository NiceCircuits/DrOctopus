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
#include <stdbool.h>

/**
 * Initialize I2C.
 * @return 0 if OK.
 */
uint_fast8_t i2cInit(void);

/**
 * Write data over I2C. Generate whole transaction, optionally with stop bit.
 * @param addr Slave address. 7-bit format.
 * @param count Number of bytes to be transmitted.
 * @param payload Pointer to data buffer.
 * @return 0 if OK.
 */
uint_fast8_t i2cWriteTransaction(uint8_t addr, uint8_t count, uint8_t* payload);

#endif /* I2C_H_ */
