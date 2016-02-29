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

/// Transfer mode for I2C functions.
typedef enum {
	/// Don't generate (re)start sequence, don't generate stop bit.
	i2cTransferModeNoStartStop,
	/// Generate (re)start sequence, don't generate stop bit.
	i2cTransferModeStart,
	/// Don't generate (re)start sequence, generate stop bit after transaction.
	i2cTransferModeStop,
	/// Generate (re)start sequence, generate stop bit after transaction
	i2cTransferModeStartStop
} i2cTransferMode_t;

/**
 * Initialize I2C.
 * @return 0 if OK.
 */
uint_fast8_t i2cInit(void);

/**
 * Write data over I2C. Generate whole transaction, optionally with stop bit.
 * @param addr Slave address. 7-bit format.
 * @param count Number of bytes to be transimtted.
 * @param payload Pointer to data buffer.
 * @return 0 if OK.
 */
uint_fast8_t i2cWriteTransaction(uint8_t addr, uint8_t count, uint8_t* payload);

/**
 * Send a single byte over I2C.
 * @param data Data to be sent.
 * @return (N)ACK bit state. 0: ACK, 1: NACK.
 */
bool i2cWriteByte(uint8_t data);

/**
 * Generate I2C stop bit.
 * @return 0 if OK.
 */
uint_fast8_t i2cStopBit();

/**
 * Generate I2C start bit.
 * @return 0 if OK.
 */
uint_fast8_t i2cStartBit();

#endif /* I2C_H_ */
