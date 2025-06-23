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

long getDistance(int triggerPin, int echoPin) {
  const int numMeasurements = 10;
  long distances[numMeasurements];
  const long minRange = 2;    // Minimalny zasięg czujnika w cm
  const long maxRange = 400;  // Maksymalny zasięg czujnika w cm

  auto measure = [](int trig, int echo) -> long {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long duration = pulseIn(echo, HIGH, 30000);  // timeout 30ms = max ~500 cm
    return duration * 0.0343 / 2;
  };

  for (int i = 0; i < numMeasurements; i++) {
    distances[i] = measure(triggerPin, echoPin);
    delay(20);
  }

  // sortowanie rosnąco
  for (int i = 0; i < numMeasurements - 1; i++) {
    for (int j = i + 1; j < numMeasurements; j++) {
      if (distances[i] > distances[j]) {
        long tmp = distances[i];
        distances[i] = distances[j];
        distances[j] = tmp;
      }
    }
  }

  // mediana
  long median;
  if (numMeasurements % 2 == 0) {
    median = (distances[numMeasurements / 2 - 1] + distances[numMeasurements / 2]) / 2;
  } else {
    median = distances[numMeasurements / 2];
  }

  if (median < minRange || median > maxRange) {
    return -1;
  }

  return median;
}

extern volatile unsigned long leftWheelCount;
extern volatile unsigned long rightWheelCount;

float calculateDistance(unsigned long count) {
  return (count * WHEEL_DIAMETER_CM * PI) / 100.0; // w metrach
}

void displayDistance(float distances[2]) {
  noInterrupts();
  unsigned long leftCount = leftWheelCount;
  unsigned long rightCount = rightWheelCount;
  interrupts();

  distances[0] = calculateDistance(leftCount);
  distances[1] = calculateDistance(rightCount);
}

