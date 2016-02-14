/**
  ******************************************************************************
  * @file    servo.h
  * @author  piotr@nicecircuits.com
  * @date    2016-02-13
  * @brief   
  ******************************************************************************
*/
#ifndef SERVO_H_
#define SERVO_H_

#include <inttypes.h>

/**
 * Initialize servo pins and timers.
 * @return 0 if OK.
 */
uint_fast8_t servoInit();

/**
 * Loop for servo driver. Must be called at least every 20ms.
 * @return 0 if OK.
 */
uint_fast8_t servoLoop();

/**
 * Move servo to position.
 * @param servo Servo number.
 * @param pos New position. 0 is center, +-1000 is standard range (1..2 ms).
 * +-2000 is max range (0.5..2.5 ms).
 * @param Speed servo speed. Max increment of servo position in one cycle (20ms).
 * @return 0 if OK.
 */
uint_fast8_t servoCmd(uint8_t servo, int_fast32_t pos, int_fast32_t speed);

/**
 * Enable/disable servo.
 * @param servo Servo number.
 * @param enabled New enabled state.
 * @return 0 if OK.
 */
uint_fast8_t servoEnable(uint8_t servo, FunctionalState enabled);

#endif /* SERVO_H_ */
