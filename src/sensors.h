#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <SD.h>

void setupSensors();
long readUltrasonicDistance(int trigPin, int echoPin);

void logSensorData(File &file, int measurement,
                   float leftDist, float frontDist, float rightDist,
                   float leftWheelDist, float rightWheelDist);

long getDistance(int triggerPin, int echoPin);
void displayDistance(float distances[2]);

#endif

