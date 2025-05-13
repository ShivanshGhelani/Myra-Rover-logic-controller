#include <Arduino.h>
#include "ultrasonic.h"

void initUltrasonic() {
    pinMode(TRIG_FRONT, OUTPUT); pinMode(ECHO_FRONT, INPUT);
    pinMode(TRIG_FRONT_RIGHT, OUTPUT); pinMode(ECHO_FRONT_RIGHT, INPUT);
    pinMode(TRIG_FRONT_LEFT, OUTPUT); pinMode(ECHO_FRONT_LEFT, INPUT);
    // pinMode(TRIG_REAR_RIGHT, OUTPUT); pinMode(ECHO_REAR_RIGHT, INPUT);
    // pinMode(TRIG_REAR_LEFT, OUTPUT); pinMode(ECHO_REAR_LEFT, INPUT);
}

long readUltrasonic(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void ultrasonicTask(void *pvParameters) {
    while (1) {
        sensorData.front = readUltrasonic(TRIG_FRONT, ECHO_FRONT);
        sensorData.frontRight = readUltrasonic(TRIG_FRONT_RIGHT, ECHO_FRONT_RIGHT);
        sensorData.frontLeft = readUltrasonic(TRIG_FRONT_LEFT, ECHO_FRONT_LEFT);
        // sensorData.rearRight = readUltrasonic(TRIG_REAR_RIGHT, ECHO_REAR_RIGHT);
        // sensorData.rearLeft = readUltrasonic(TRIG_REAR_LEFT, ECHO_REAR_LEFT);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
