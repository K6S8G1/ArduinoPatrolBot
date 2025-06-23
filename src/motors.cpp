// motors.cpp
#include "motors.h"
#include "config.h"

void setupMotors() {
  pinMode(LEFT_MOTOR_DIR, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
}

void moveForward(int speed) {
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  analogWrite(LEFT_MOTOR_PWM, speed);
  analogWrite(RIGHT_MOTOR_PWM, speed);
}

void moveLeft(int speed) {
  digitalWrite(LEFT_MOTOR_DIR, LOW);
  digitalWrite(RIGHT_MOTOR_DIR, HIGH);
  analogWrite(LEFT_MOTOR_PWM, speed);
  analogWrite(RIGHT_MOTOR_PWM, speed);
}

void moveRight(int speed) {
  digitalWrite(LEFT_MOTOR_DIR, HIGH);
  digitalWrite(RIGHT_MOTOR_DIR, LOW);
  analogWrite(LEFT_MOTOR_PWM, speed);
  analogWrite(RIGHT_MOTOR_PWM, speed);
}

void stopMotors() {
  analogWrite(LEFT_MOTOR_PWM, 0);
  analogWrite(RIGHT_MOTOR_PWM, 0);
}
