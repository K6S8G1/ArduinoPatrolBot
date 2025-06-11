// line_following.cpp
#include "line_following.h"
#include "config.h"
#include "sensors.h"
#include "globals.h"
#include "motors.h"

void BangBangControl() {
  int left = digitalRead(LEFT_LINE_SENSOR);
  int mid = digitalRead(MIDDLE_LINE_SENSOR);
  int right = digitalRead(RIGHT_LINE_SENSOR);

  // Główna linia – jedź prosto
  if (left == LOW && mid == HIGH && right == LOW) {
    moveForward(180);
  }

  // Korekta w lewo
  else if (left == HIGH && right == LOW) {
    moveRight(180);
  }

  // Korekta w prawo
  else if (left == LOW && right == HIGH) {
    moveLeft(180);
  }

  // Zakończenie – brak linii
  else if (left == HIGH && mid == HIGH && right == HIGH) {
    stopMotors();
    Serial.println("Koniec");
    newMove = false;
  }

  // Inne przypadki
  else {
    moveForward(140);
  }

  // Co jakiś czas loguj dane
  unsigned long currentMillis = millis();
  static unsigned long lastLog = 0;
  if (currentMillis - lastLog >= 300) {
    lastLog = currentMillis;
    float leftDist = getDistance(LEFT_SENSOR_TRIG, LEFT_SENSOR_ECHO);
    float frontDist = getDistance(FRONT_SENSOR_TRIG, FRONT_SENSOR_ECHO);
    float rightDist = getDistance(RIGHT_SENSOR_TRIG, RIGHT_SENSOR_ECHO);

    float distances[2];
    displayDistance(distances);

    File dataFile = SD.open(mapping ? "map.csv" : "patrol.csv", FILE_WRITE);
    if (dataFile) {
      logSensorData(dataFile, measurementNumber++, leftDist, frontDist, rightDist, distances[0], distances[1]);
      dataFile.close();
    } else {
      Serial.println("Błąd otwierania pliku CSV");
    }
  }
}

