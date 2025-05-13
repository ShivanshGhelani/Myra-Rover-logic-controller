#ifndef AUTO_MODE 
#define AUTO_MODE

#define THRESHOLD_FRONT 30
#define THRESHOLD_SIDE 15
#define THRESHOLD_REAR 15

#define MIN_DIST 10  // cm
#define MAX_DIST 50  // cm
#define MIN_SPEED 155
#define MAX_SPEED 255
#define MAX_RETRIES 3

extern bool autonomousMode;

// int getSpeed(int distance);
// int getSmoothSpeed(int targetSpeed);
// uint8_t getBestMove();
void avoidObstacle();
void decideMovement();


#endif