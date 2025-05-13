#include "esp_now_sender.h"
#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>

uint8_t broadcastAddress[6] = {0x94, 0x54, 0xC5, 0xA8, 0x14, 0x90}; // Replace with actual MAC address of the receiver

const char *ssid = "ESP-Now-Sender";
const char *password = "12345678";



void initESPNow() {
    // Avoid calling WiFi.disconnect() to preserve the connection between AP and STA modes.
    
    // If not already in STA mode, initialize it explicitly
    if (WiFi.getMode() == WIFI_AP) {
        WiFi.mode(WIFI_STA);  // Switch to STA mode (if needed)
    }

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Set up the peer information for ESP-NOW
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = WiFi.channel();  // Ensure both AP and STA are on the same channel
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    Serial.println("ESP-NOW Initialized");
}
void sendCommand(uint8_t command, uint8_t speed) {
    Message message;
    message.command = command;
    message.speed = speed;

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&message, sizeof(message));
    // vTaskDelay(pdMS_TO_TICKS(200));

    if (result == ESP_OK) {
        Serial.println("Command sent successfully");
        // Serial.print(message.command);
    } else {
        Serial.print("Error sending command, error code: ");
        Serial.println(result);  // Display the error code
    }
}


void processCommand(int commandByte, int speed) {
    // Ensure command and speed are within bounds of uint8_t
    uint8_t command = (uint8_t) commandByte;  // Command byte (0-255)
    uint8_t speedValue = (speed == -1) ? 255 : (uint8_t) speed;  // Default to 255 if no speed is provided

    // Send the command to ESP32 via ESP-NOW
    sendCommand(command, speedValue);
}
