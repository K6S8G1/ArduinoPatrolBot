// sensors.cpp
#include "sensors.h"
#include "config.h"
#include "globals.h"
#include <SD.h>

void setupSensors() {
  pinMode(FRONT_SENSOR_TRIG, OUTPUT);
  pinMode(FRONT_SENSOR_ECHO, INPUT);
  pinMode(LEFT_SENSOR_TRIG, OUTPUT);
  pinMode(LEFT_SENSOR_ECHO, INPUT);
  pinMode(RIGHT_SENSOR_TRIG, OUTPUT);
  pinMode(RIGHT_SENSOR_ECHO, INPUT);

  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(MIDDLE_LINE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_SENSOR, INPUT);

  digitalWrite(FRONT_SENSOR_TRIG, LOW);
  digitalWrite(LEFT_SENSOR_TRIG, LOW);
  digitalWrite(RIGHT_SENSOR_TRIG, LOW);
}

long readUltrasonicDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2;
  return distance;
}

void logSensorData(File &file, int measurement, float leftDist, float frontDist, float rightDist, float leftWheelDist, float rightWheelDist) {
  if (file) {
    file.print(measurement);
    file.print(",");
    file.print(leftDist);
    file.print(",");
    file.print(frontDist);
    file.print(",");
    file.print(rightDist);
    file.print(",");
    file.print(leftWheelDist);
    file.print(",");
    file.println(rightWheelDist);
    file.flush();
  }
}
