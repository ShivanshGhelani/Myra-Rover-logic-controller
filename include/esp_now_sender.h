#ifndef ESP_NOW_SENDER_H
#define ESP_NOW_SENDER_H


#include <esp_now.h>
#include <WiFi.h>
// Movement commands (0x01 to 0x08)
#define MOVE_FORWARD            0x01
#define MOVE_BACKWARD           0x02
#define MOVE_FORWARD_LEFT       0x05
#define MOVE_FORWARD_RIGHT      0x06
#define MOVE_BACKWARD_LEFT      0x07
#define MOVE_BACKWARD_RIGHT     0x08

// Turn commands (0x03 to 0x04)
#define TURN_LEFT               0x03
#define TURN_RIGHT              0x04

// Spin commands (0x0A to 0x0B)
#define SPIN_CLOCKWISE          0x09
#define SPIN_COUNTERCLOCKWISE   0x0A

// // Reverse turn commands (0x0C to 0x0D)
// #define TURN_LEFT_REVERSE       0x0D
// #define TURN_RIGHT_REVERSE      0x0E

// # Diagonal movement commands (0x0E to 0x11)
#define DIAGONAL_LEFT           0x0B
#define DIAGONAL_RIGHT          0x0C
#define DIAGONAL_LEFT_REVERSE   0x0D
#define DIAGONAL_RIGHT_REVERSE  0x0E
// Special Command
#define STOP                    0x00

#define MANAUL_MODE_AUTONOMOUS_MODE 0x0F
#define VOICE_COMMAND 0x16
// Broadcast address (replace with the MAC address of the receiver if needed)
extern uint8_t broadcastAddress[6];
extern const char *ssid;
extern const char *password;

struct Message {
    uint8_t command;
    uint8_t speed; // Command to send, default to 255 if not received
};
void processCommand(int commandByte, int speed);
void initESPNow();
void sendCommand(uint8_t command, uint8_t speed = 255);

#endif // ESP_NOW_SENDER_H
