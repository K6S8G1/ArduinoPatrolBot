#include "storage.h"

bool initStorage() {
  if (!SD.begin()) {
    Serial.println("Błąd: karta SD nie została wykryta.");
    return false;
  }
  Serial.println("Karta SD została poprawnie zainicjalizowana.");
  return true;
}

File openMapFile() {
  return SD.open("map.csv", FILE_WRITE);
}

File openPatrolFile() {
  return SD.open("patrol.csv", FILE_WRITE);
}
