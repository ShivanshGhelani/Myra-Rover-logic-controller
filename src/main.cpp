#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "esp_now_sender.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ultrasonic.h"
#include "wifi_commands.h"
#include "auto_mode.h"
#include "voice_command_mode.h"

// #define LED_BUILTIN 1  // Built-in LED pin for ESP32

WiFiServer server(80);
TaskHandle_t UltrasonicTaskHandle;
bool autonomousMode = false;
bool voiceCommandmode = false;  // Initially in manual mode
unsigned long lastCommandTime = 0;

UltrasonicData sensorData;

void setup() {
    Serial.begin(115200);
    // delay(1000);  // Give time for Serial Monitor to open
    // pinMode(LED_BUILTIN, OUTPUT);  // Initialize the built-in LED pin
    digitalWrite(LED_BUILTIN, LOW);  // Turn off the LED

    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(ssid, password);
    server.begin();
    initESPNow();
    initUltrasonic();
    
    xTaskCreatePinnedToCore(
        ultrasonicTask,  
        "UltrasonicTask", 
        4096, 
        NULL, 
        1, 
        &UltrasonicTaskHandle, 
        1  
    );
}

void loop() {
    processWiFiCommands();

    if (autonomousMode) {
        decideMovement();
    }
    else if (voiceCommandmode) {
        voiceCommand();
    }
    // digitalWrite(LED_BUILTIN, HIGH);  // Turn on the LED
    // vTaskDelay(pdMS_TO_TICKS(500));
    // digitalWrite(LED_BUILTIN, LOW);  // Turn off the LED
    vTaskDelay(pdMS_TO_TICKS(200));
}
