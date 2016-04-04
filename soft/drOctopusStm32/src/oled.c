/**
 ******************************************************************************
 * @file    oled.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-22
 * @brief   SSD1306 128x64 OLED display library.
 ******************************************************************************
 */

#include "oled.h"
#include "delay.h"
#include "i2c.h"
#include "debug.h"

// ---------- Private variables. ----------
debugSource_t oledDebugSource;
/// u8glib object.
u8g_t u8g;
/// Force generate I2C start sequence in next write.
bool generateStart = 1;
/// Select communication mode: 0: command 1: data.
bool oledCmdMode = 0;
/// Buffer for OLED communication functions.
uint8_t oledCommunicationBuffer[256];

// ---------- Private functions. ----------
uint8_t u8g_communication(u8g_t *u8g, uint8_t msg, uint8_t arg_val,
		void *arg_ptr);

// ---------- Public functions. ----------
uint_fast8_t oledInit(void) {
	oledDebugSource = debugNewSource("Oled");
	debugSourceEnable(oledDebugSource, ENABLE);
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
 * @return 1 if OK.
 */
uint8_t u8g_communication(u8g_t *u8g __attribute__ ((unused)), uint8_t msg, uint8_t arg_val,
		void *arg_ptr) {
	uint_fast8_t result, i;

	switch (msg) {
	case U8G_COM_MSG_STOP:
		//debugPrintln(oledDebugSource, "stop");
		break;

	case U8G_COM_MSG_INIT:
		debugPrintln(oledDebugSource, "init");
		i2cInit();
		break;

	case U8G_COM_MSG_ADDRESS: // define cmd (arg_val = 0) or data mode (arg_val = 1)
		debugPrintln(oledDebugSource, "addr: %1x", arg_val);
		// Generate I2C start sequence in next write.
		generateStart = 1;
		// Select communication mode.
		oledCmdMode = arg_val;
		// Generate stop bit to complete previous transaction.
		i2cStopBit();
		break;

	case U8G_COM_MSG_CHIP_SELECT:
		debugPrintln(oledDebugSource, "cs: %1x", arg_val);
		generateStart = 1;
		if (arg_val == 0) {
			// Disable communication.
			i2cStopBit();
		} else {
			// Enable communication.
		}
		break;

	case U8G_COM_MSG_RESET:
		debugPrintln(oledDebugSource, "rst");
		break; // Not available.

	case U8G_COM_MSG_WRITE_BYTE:
		debugPrintln(oledDebugSource, "write: %02x", arg_val);
		if (generateStart) {
			i2cStartBit();
			// I2C address.
			i2cWriteByte(OLED_I2C_ADDR << 1);
			// SSD1306 control byte.
			i2cWriteByte((oledCmdMode & 0x01) << 6);
			generateStart = 0;
		}
		result = i2cWriteByte(arg_val);
		if (result != 0) { // error
//			i2cStopBit();
			return 0; // error flag
		}
		break;

	case U8G_COM_MSG_WRITE_SEQ:
	case U8G_COM_MSG_WRITE_SEQ_P: {
		debugPrintln(oledDebugSource, "write: %d %p", arg_val, arg_ptr);
		if (generateStart) {
			i2cStartBit();
			// I2C address.
			i2cWriteByte(OLED_I2C_ADDR << 1);
			// SSD1306 control byte.
			i2cWriteByte((oledCmdMode & 0x01) << 6);
			generateStart = 0;
		}
		for (i = 0; i < arg_val; i++) {
			result = i2cWriteByte(((uint8_t*) arg_ptr)[i]);
		}
		if (result != 0) { // error
//			i2cStopBit();
			return 0; // error flag
		}
		break;
	}
	default: {
		return 0;
	}
	}
	return 1;
}

#if defined(TEST_MODE) && TEST_MODE == TEST_MODE_OLED

void draw(uint8_t pos) {
	u8g_SetFont(&u8g, u8g_font_unifont);
	u8g_DrawStr(&u8g, 0, 12 + pos, "Hello World!");
}

int main(void) {
	uint8_t pos = 0;
	defaultInit();
	oledInit();

	for (;;) {
		/* picture loop */
		u8g_FirstPage(&u8g);
		do {
			draw(pos);
		} while (u8g_NextPage(&u8g));

		/* refresh screen after some delay */
		u8g_Delay(100);

		/* update position */
		pos++;
		pos &= 15;
	}
}
#endif // TEST_MODE == TEST_MODE_OLED
