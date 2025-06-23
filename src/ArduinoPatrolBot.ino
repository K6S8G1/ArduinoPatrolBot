#include "config.h"
#include "motors.h"
#include "sensors.h"
#include "line_following.h"
#include "wifi_comms.h"
#include "storage.h"
#include "globals.h"

#include <SPI.h>
#include <SD.h>

// Dane
volatile unsigned long lastLeftInterrupt = 0;
volatile unsigned long lastRightInterrupt = 0;
unsigned long prevMillis = 0;
int measurementCounter = 0;


File dataFile;

void leftWheelISR() {
  unsigned long now = millis();
  if (now - lastLeftInterrupt > DEBOUNCE_DELAY_MS) {
    leftWheelCount++;
    lastLeftInterrupt = now;
  }
}

void rightWheelISR() {
  unsigned long now = millis();
  if (now - lastRightInterrupt > DEBOUNCE_DELAY_MS) {
    rightWheelCount++;
    lastRightInterrupt = now;
  }
}

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

  setupMotors();
  setupSensors();
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), leftWheelISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), rightWheelISR, RISING);

  if (!initStorage()) while (true);
  dataFile = mapping ? openMapFile() : openPatrolFile();

  setupWiFi("INEA-2126_2.4G", "SdYER2PC");
  Serial.println("Zawartość karty SD:");
  File root = SD.open("/");
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;
    Serial.println(entry.name());
    entry.close();
}
}

void loop() {
  handleClient();  // Obsługa WebSocket

  if (!newMove) return;

  BangBangControl();

  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= MEASUREMENT_INTERVAL) {
    prevMillis = currentMillis;

    float leftDist = readUltrasonicDistance(LEFT_SENSOR_TRIG, LEFT_SENSOR_ECHO);
    float frontDist = readUltrasonicDistance(FRONT_SENSOR_TRIG, FRONT_SENSOR_ECHO);
    float rightDist = readUltrasonicDistance(RIGHT_SENSOR_TRIG, RIGHT_SENSOR_ECHO);

    float leftWheelCM = leftWheelCount * (PI * WHEEL_DIAMETER_CM);
    float rightWheelCM = rightWheelCount * (PI * WHEEL_DIAMETER_CM);

    logSensorData(dataFile, measurementCounter++, leftDist, frontDist, rightDist, leftWheelCM, rightWheelCM);
  }
}
