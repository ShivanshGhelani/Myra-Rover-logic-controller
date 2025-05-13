#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#define TRIG_FRONT 11
#define ECHO_FRONT 12
#define TRIG_FRONT_RIGHT 19
#define ECHO_FRONT_RIGHT 20
#define TRIG_FRONT_LEFT 14
#define ECHO_FRONT_LEFT 13
// #define TRIG_REAR_RIGHT 9
// #define ECHO_REAR_RIGHT 10
// #define TRIG_REAR_LEFT 5
// #define ECHO_REAR_LEFT 4

struct UltrasonicData {
    long front;
    long frontRight;
    long frontLeft;
    // long rearRight;
    // long rearLeft;
};

extern UltrasonicData sensorData;

void initUltrasonic();
long readUltrasonic(int trigPin, int echoPin);
void ultrasonicTask(void *pvParameters);

#endif // ULTRASONIC_H
