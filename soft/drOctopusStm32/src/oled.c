/**
 ******************************************************************************
 * @file    oled.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-22
 * @brief   OLED display library.
 ******************************************************************************
 */

#include "oled.h"
#include "delay.h"
#include "i2c.h"
#include "debug.h"

// ---------- Private variables. ----------
debugSource_t debugOled;
u8g_t u8g;

// ---------- Private functions. ----------
uint8_t u8g_communication(u8g_t *u8g, uint8_t msg, uint8_t arg_val,
		void *arg_ptr);

// ---------- Public functions. ----------
uint_fast8_t oledInit(void) {
	debugOled = debugNewSource("Oled");
	debugSourceEnable(debugOled, ENABLE);
	i2cInit();
	u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x64_i2c, u8g_communication);
	u8g_SetDefaultForegroundColor(&u8g);
	return 0;
}

// ---------- Functions needed by u8glib ----------
/**
 * Delay by "val" milliseconds. Function needed by u8glib.
 * @param val
 */
void u8g_Delay(uint16_t val) {
	delayMs(val);
}

/**
 * Delay be one microsecond. Function needed by u8glib.
 */
void u8g_MicroDelay(void) {
	delayUs(1);
}

/**
 * Delay by 10 microseconds. Function needed by u8glib.
 */
void u8g_10MicroDelay(void) {
	delayUs(10);
}

/**
 * Display communication procedure for u8glib.
 * @param u8g u8glib structure.
 * @param msg Message from u8glib.
 * @param arg_val Optional argument.
 * @param arg_ptr Optional argument pointer.
 * @return 1.
 */
uint8_t u8g_communication(u8g_t *u8g, uint8_t msg, uint8_t arg_val,
		void *arg_ptr) {
	debugPrintln(debugOled, "u8glib: 0x%2x 0x%2x %p", msg, arg_val, arg_ptr);
	delayMs(10);
	switch (msg) {
	case U8G_COM_MSG_STOP:
		break;

	case U8G_COM_MSG_INIT:
		oledInit();
		break;

	case U8G_COM_MSG_ADDRESS: // define cmd (arg_val = 0) or data mode (arg_val = 1)
		break; // Not available.

	case U8G_COM_MSG_CHIP_SELECT:
		break; // Not available.

	case U8G_COM_MSG_RESET:
		break; // Not available.

	case U8G_COM_MSG_WRITE_BYTE:
		//spi_out(arg_val);
		u8g_MicroDelay();
		break;

	case U8G_COM_MSG_WRITE_SEQ:
	case U8G_COM_MSG_WRITE_SEQ_P: {
		register uint8_t *ptr = arg_ptr;
		while (arg_val > 0) {
			//spi_out(*ptr++);
			arg_val--;
		}
	}
		break;
	default: {
		return 0;
	}
	}
	return 1;
}

#if TEST_MODE == TEST_MODE_OLED
int main(void) {
	uint8_t addr;

	defaultInit();
	oledInit();

	for (;;) {
	}
}
#endif // TEST_MODE == TEST_MODE_OLED
