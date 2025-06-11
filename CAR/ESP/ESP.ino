#include <Arduino.h>
#include <cstdio>
#include <cstdlib>
#include "gyro.h"
#include "udpConnection.h"
#include "HardwareSerial.h"

HardwareSerial ArduinoSerial(2); // Use UART1 on ESP32

MPUClass MPUHorizontal(1);
MPUClass MPUVertical(2);
float* ypr;
char packet[50];

void setup() {
  Serial.begin(115200);
  // MPUHorizontal.SetupGyro();
  // delay(5000);
  // UDPSetup();
  // delay(5000);
  ArduinoSerial.begin(115200, SERIAL_8N1, 16, 17);  // RX=3, TX=1
}

void loop() {
  // ypr = MPUHorizontal.getYawPitchRoll();

  // snprintf(packet, 50, "%.2f,%.2f,%.2f\n", ypr[0], ypr[1], ypr[2]);
  // Serial.print(packet);
  // UDPSendPacket(packet);
  // delay(20);

  // ArduinoSerial.println("Hello from ESP32");
  // delay(1000);
  if (ArduinoSerial.available()) {
    String msg = ArduinoSerial.readStringUntil('\n');
    Serial.println("From Arduino: " + msg);
  }
}