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
 * Move servo to position.
 * @param servo servo number.
 * @param pos new position. 0 is center, +-1000 is standard range (1..2 ms).
 * +-2000 is max range (0.5..2.5 ms).
 * @return 0 if OK.
 */
uint_fast8_t servoCmd(uint8_t servo, int_fast32_t pos);


#endif /* SERVO_H_ */
