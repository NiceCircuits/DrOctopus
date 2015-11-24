/*
 * servos.cpp
 *
 *  Created on: 2015-11-24
 *      Author: Piotr Nowicki
 */
#include <Servo.h>

Servo servo1, servo2, servo3, servo4;

void servosInit()
{
	servo1.attach(7);
	servo2.attach(8);
	servo3.attach(9);
	servo4.attach(10);
	servo1.writeMicroseconds(1500);  // set servo to mid-point
	servo2.writeMicroseconds(1500);  // set servo to mid-point
	servo3.writeMicroseconds(1500);  // set servo to mid-point
	servo4.writeMicroseconds(1500);  // set servo to mid-point
}


