// motors.h
#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

void setupMotors();
void moveForward(int speed);
void moveLeft(int speed);
void moveRight(int speed);
void stopMotors();

#endif
