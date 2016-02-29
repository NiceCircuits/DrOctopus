/**
 ******************************************************************************
 * @file    i2c.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-17
 * @brief   I2C driver. After many evenings spent fighting with STM32 I2C,
 * it's implemented by bit-banging.
 ******************************************************************************
 */

#include "i2c.h"
#include "config.h"
#include "delay.h"

// ---------- Private variables. ----------
/// I2C GPIO structures, SDA, SCL
static GPIO_TypeDef * const i2cGpios[2] = I2C_GPIOS;
/// I2C GPIO pins, SDA, SCL
static uint16_t const i2cPins[2] = I2C_PINS;
bool i2cStarted = 0;

// ---------- Private type definitions. ----------
typedef enum {
	SDA = 0, SCL = 1
} i2c_pin_t;

// ---------- Private functions declarations. ----------
/// Set/reset I2C pin output.
void i2cPinCmd(i2c_pin_t pin, BitAction value);
/// Return state of I2C GPIO input.
bool i2cPinState(i2c_pin_t pin);
/// Send single bit over I2C.
uint_fast8_t i2cWriteBit(BitAction value);
/// Read single byte over I2C.
bool i2cReadBit();
/// Delay 1/4 I2C bit length.
uint_fast8_t i2cDelay1_4();
/// Delay 1/2 I2C bit length.
uint_fast8_t i2cDelay1_2();

// ---------- Public functions. ----------
uint_fast8_t i2cInit(void) {

	GPIO_InitTypeDef gpio;
	uint_fast8_t i;

	// Init I2C GPIOs.
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_OD;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	for (i = 0; i < 2; i++) {
		gpio.GPIO_Pin = i2cPins[i];
		GPIO_Init(i2cGpios[i], &gpio);
		GPIO_WriteBit(i2cGpios[i], i2cPins[i], Bit_SET);
	}

	return 0;
}

uint_fast8_t i2cWriteTransaction(uint8_t addr, uint8_t count, uint8_t* payload) {
	uint8_t i;
	uint_fast8_t nack;
	i2cStartBit();
	nack = i2cWriteByte(addr << 1);
	if (nack == 0) {
		for (i = 0; i < count; i++) {
			i2cWriteByte(payload[i]);
		}
	}
	i2cStopBit();
	return nack;
}

bool i2cWriteByte(uint8_t data) {
	uint_fast8_t i;
	for (i = 0; i < 8; i++) {
		i2cWriteBit((data & 0x80) != 0);
		data = data << 1;
	}
	return i2cReadBit();
}

uint_fast8_t i2cStopBit() {
	// Initial state: SDA is high, SCL is low.
	i2cPinCmd(SDA, Bit_RESET);
	i2cDelay1_4();
	i2cPinCmd(SCL, Bit_SET);
	i2cDelay1_4();
	i2cPinCmd(SDA, Bit_SET);
	i2cDelay1_2();
	i2cStarted = false;
	return 0;
}

uint_fast8_t i2cStartBit() {
	// Initial state: SDA is high, SCL is high if start, low if repeated start.
	if (i2cStarted) {
		// Repeated start.
		i2cDelay1_4();
		i2cPinCmd(SCL, Bit_SET);
		i2cDelay1_4();
	}
	i2cPinCmd(SDA, Bit_RESET);
	i2cDelay1_4();
	i2cPinCmd(SCL, Bit_RESET);
	i2cDelay1_4();
	i2cStarted = true;
	return 0;
}

// ---------- Private functions. ----------
uint_fast8_t i2cWriteBit(BitAction value) {
	// Initial state: SDA is high, SCL is low.
	i2cPinCmd(SDA, value);
	i2cDelay1_4();
	i2cPinCmd(SCL, Bit_SET);
	i2cDelay1_2();
	i2cPinCmd(SCL, Bit_RESET);
	i2cDelay1_4();
	return 0;
}

bool i2cReadBit() {
	bool ret;
	// Initial state: SDA is high, SCL is low.
	i2cPinCmd(SDA, Bit_SET);
	i2cDelay1_4();
	i2cPinCmd(SCL, Bit_SET);
	i2cDelay1_4();
	ret = i2cPinState(SDA);
	i2cDelay1_4();
	i2cPinCmd(SCL, Bit_RESET);
	i2cDelay1_4();
	return ret;
}

uint_fast8_t i2cDelay1_4() {
	return delayUs((I2C_BIT_TIME_US + 3) / 4);
}

uint_fast8_t i2cDelay1_2() {
	return delayUs((I2C_BIT_TIME_US + 1) / 2);
}

void i2cPinCmd(i2c_pin_t pin, BitAction value) {
	GPIO_WriteBit(i2cGpios[pin], i2cPins[pin], value);
}

bool i2cPinState(i2c_pin_t pin) {
	return (bool) GPIO_ReadInputDataBit(i2cGpios[pin], i2cPins[pin]);
}

#if TEST_MODE == TEST_MODE_I2C

int main(void) {
	uint8_t addr;
	uint8_t payload[] = { 1, 2, 3, 4 };

	defaultInit();
	i2cInit();

	addr = 0x3C;
	for (;;) {
		i2cWriteTransaction(addr, 4, payload);
		addr++;
		if (addr >= 0x3D) {
			addr = 0x3B;
		}
	}
}
#endif // TEST_MODE == TEST_MODE_I2C
