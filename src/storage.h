#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#include <SD.h>

bool initStorage();
File openMapFile();
File openPatrolFile();

#endif
