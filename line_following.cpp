// line_following.cpp
#include "line_following.h"
#include "config.h"
#include "globals.h"
#include "motors.h"

void BangBangControl() {
  int left = digitalRead(LEFT_LINE_SENSOR);
  int middle = digitalRead(MIDDLE_LINE_SENSOR);
  int right = digitalRead(RIGHT_LINE_SENSOR);

  if (left == LOW && middle == HIGH && right == LOW) {
    moveForward(SPEED_NORMAL);
  }
  else if (left == HIGH && middle == LOW && right == LOW) {
    moveLeft(SPEED_NORMAL);
  }
  else if (left == LOW && middle == LOW && right == HIGH) {
    moveRight(SPEED_NORMAL);
  }
  else if (left == HIGH && middle == HIGH && right == HIGH) {
    stopMotors(); // Całkowita utrata linii lub koniec trasy
  }
  else {
    moveForward(SPEED_NORMAL / 2); // Ostrożnie do przodu
  }
}
