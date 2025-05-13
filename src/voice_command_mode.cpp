#include <Arduino.h>
#include "voice_command_mode.h"
#include "esp_now_sender.h"
#include "ultrasonic.h"

extern WiFiServer server;
extern bool autonomousMode;
extern bool voiceCommandmode;
extern unsigned long lastCommandTime;


void voiceCommand() {
    WiFiClient client = server.available();
    if (client) {
        String command = "";
        while (client.available()) {
            char c = client.read();
            if (c == '\n') {
                command.trim();
                if (command.startsWith("0x")) {
                    int commandByte = strtol(command.substring(2, 4).c_str(), NULL, 16);
                    Serial.print("WiFi Command: ");
                    Serial.println(commandByte);

                    if (commandByte == 0x0F) {
                        autonomousMode = !autonomousMode;
                        Serial.print("Mode changed to: ");
                        Serial.println(autonomousMode ? "Autonomous" : "Manual");
                    } 
                    else if  (commandByte == 0x16) {
                        voiceCommandmode = !voiceCommandmode;
                        Serial.print("Mode changed to: ");
                        Serial.println(voiceCommandmode ? "Voice Command" : "Manual");
                    }
                    else {
                        processCommand(commandByte, 255);
                        if (!autonomousMode) {
                            lastCommandTime = millis();
                        }
                    }
                }
                break;
            } else {
                command += c;
            }
        }
        client.stop();
    }
}
