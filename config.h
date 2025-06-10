// config.h
#ifndef CONFIG_H
#define CONFIG_H

// --- PINY ---
#define RIGHT_ENCODER        2
#define LEFT_ENCODER         3
#define RIGHT_MOTOR_DIR      4
#define RIGHT_MOTOR_PWM      5
#define LEFT_MOTOR_PWM       6
#define LEFT_MOTOR_DIR       7

#define FRONT_SENSOR_TRIG    A0
#define FRONT_SENSOR_ECHO    A1
#define RIGHT_SENSOR_TRIG    A2
#define RIGHT_SENSOR_ECHO    A3
#define LEFT_SENSOR_TRIG     A4
#define LEFT_SENSOR_ECHO     A5

#define LEFT_LINE_SENSOR     9
#define MIDDLE_LINE_SENSOR   8
#define RIGHT_LINE_SENSOR    0

#define MICROSD_CS_PIN       10

// --- STAŁE ---
#define WHEEL_DIAMETER_CM    6.6
#define SPEED_NORMAL         150
#define SERIAL_BAUD_RATE     115200
#define DEBOUNCE_DELAY_MS    250
#define MEASUREMENT_INTERVAL 200

#endif
