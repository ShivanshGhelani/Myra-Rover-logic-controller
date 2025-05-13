#include <Arduino.h>
#include "esp_now_sender.h"
#include "ultrasonic.h"
#include "auto_mode.h"

int targetSpeed = 255;
const int SAFE_DISTANCE = 35;  // Distance to stop near obstacle
bool obstacleDetected = false;

void avoidObstacle() {
    // 1️⃣ Stop the Robot
    processCommand(STOP, 0);
    delay(500);  // Pause to process

    // 2️⃣ Move Left for 50 cm
    processCommand(TURN_LEFT, targetSpeed);
    delay(1000);  // Adjust timing for 50 cm movement

    // 3️⃣ Move Forward
    processCommand(MOVE_FORWARD, targetSpeed);
    delay(1200);  // Move past the obstacle

    // 4️⃣ Check Right Clearance
    if (sensorData.frontRight > SAFE_DISTANCE) {
        // 5️⃣ If Clear, Move Back Right for 50 cm
        processCommand(TURN_RIGHT, targetSpeed);
        delay(800);
    }

    // 6️⃣ Continue Forward
    processCommand(MOVE_FORWARD, targetSpeed);
    delay(300);
    processCommand(STOP,0);
}

void decideMovement() {
    if (sensorData.front < SAFE_DISTANCE) {
        avoidObstacle();  // Call obstacle avoidance logic
    } else {
        processCommand(MOVE_FORWARD, targetSpeed);  // Normal movement
    }
}





// #include <Arduino.h>
// #include "esp_now_sender.h"
// #include "ultrasonic.h"
// #include "auto_mode.h"

// int currentSpeed = 0;
// int targetSpeed = 255;
// const int SAFE_ZONE = 25;  // ✅ Start slowing down early
// const int COLLISION_ZONE = 10; // ✅ Emergency Stop if closer than 10cm  // ✅ Prevent repeating failed moves
// int retryCount = 0;
// uint8_t lastMove = STOP;

// // ✅ Smooth Speed Control
// int getSmoothSpeed(int targetSpeed) {
//     if (currentSpeed < targetSpeed) {
//         currentSpeed += 5; // ✅ Smaller acceleration steps
//     } else if (currentSpeed > targetSpeed) {
//         currentSpeed -= 5; // ✅ Smaller deceleration steps
//     }
//     return constrain(currentSpeed, MIN_SPEED, MAX_SPEED);
// }

// // ✅ Improved Obstacle Avoidance with Preemptive Stop, Priorities & Retry Logic
// uint8_t getBestMove() {
//     bool obstacleAhead = sensorData.front < SAFE_ZONE;
//     bool obstacleLeft = sensorData.frontLeft < THRESHOLD_SIDE;
//     bool obstacleRight = sensorData.frontRight < THRESHOLD_SIDE;
//     bool obstacleRearLeft = sensorData.rearLeft < THRESHOLD_REAR;
//     bool obstacleRearRight = sensorData.rearRight < THRESHOLD_REAR;
//     bool obstacleRear = obstacleRearLeft || obstacleRearRight;

//     // **1️⃣ Emergency Stop if too close**
//     if (sensorData.front < COLLISION_ZONE) {
//         retryCount = 0;  // ✅ Reset retry counter
//         return STOP;
//     }

//     // **2️⃣ Slow Down When Approaching an Obstacle**
//     if (obstacleAhead) {
//         targetSpeed = 100;  // ✅ Reduce speed near objects
//     } else {
//         targetSpeed = 255;  // ✅ Full speed if path is clear
//     }

//     // **3️⃣ If Path is Clear, Move Forward**
//     if (!obstacleAhead) {
//         retryCount = 0;  // ✅ Reset retry counter
//         return MOVE_FORWARD;
//     }

//     // **4️⃣ Stop First, Then Decide Best Move**
//     processCommand(STOP, 0);
//     delay(200);  // ✅ Short pause before thinking

//     // **5️⃣ Retry Logic: If Last Move Failed, Try a Different Move**
//     if (lastMove == MOVE_FORWARD && retryCount < MAX_RETRIES) {
//         retryCount++;
//         return (sensorData.frontLeft > sensorData.frontRight) ? MOVE_FORWARD_LEFT : MOVE_FORWARD_RIGHT;
//     }

//     // **6️⃣ If One Side is Blocked, Move Diagonally**
//     if (!obstacleLeft && obstacleRight) return MOVE_FORWARD_LEFT;
//     if (!obstacleRight && obstacleLeft) return MOVE_FORWARD_RIGHT;

//     // **7️⃣ If Both Sides Blocked, Try Moving Backward First**
//     if (!obstacleRear) {
//         retryCount = 0;
//         return (!obstacleRearLeft) ? MOVE_BACKWARD_LEFT : MOVE_BACKWARD_RIGHT;
//     }

//     // **8️⃣ If Stuck in a Corner, Try Turning Before Spinning**
//     if (obstacleAhead && obstacleRear) {
//         retryCount = 0;
//         return (sensorData.frontLeft > sensorData.frontRight) ? TURN_LEFT : TURN_RIGHT;
//     }

//     // **9️⃣ Last Resort: Spin in Open Direction**
//     retryCount = 0;
//     return (sensorData.frontLeft > sensorData.frontRight) ? SPIN_COUNTERCLOCKWISE : SPIN_CLOCKWISE;
// }

// // ✅ Decides Movement with Priority & Retries
// void decideMovement() {
//     int smoothSpeed = getSmoothSpeed(targetSpeed);
//     uint8_t bestMove = getBestMove();

//     Serial.print("Executing: ");
//     Serial.println(bestMove, HEX);

//     // ✅ If STOPPED due to obstacle, give time to react
//     if (bestMove == STOP) {
//         delay(500);
//     }

//     lastMove = bestMove;  // ✅ Store last move for retry logic
//     processCommand(bestMove, smoothSpeed);
// }
