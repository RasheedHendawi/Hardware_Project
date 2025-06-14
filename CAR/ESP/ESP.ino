#include <Arduino.h>
#include <cstdio>
#include <cstdlib>
#include "gyro.h"
#include "udpConnection.h"
#include "HardwareSerial.h"

HardwareSerial ArduinoSerial(2); // Use UART1 on ESP32

MPUClass MPUHorizontal(1);
MPUClass MPUVertical(2);
float* yprHorizontal, *yprVertical;
char packet[100];

void setup() {
  Serial.begin(115200);

  MPUHorizontal.SetupGyro();

  MPUVertical.SetupGyro();

  UDPSetup();

  ArduinoSerial.begin(115200, SERIAL_8N1, 16, 17);  // RX=3, TX=1

  delay(5000);
}

void loop() {
  if (ArduinoSerial.available()) {
    String msg = ArduinoSerial.readStringUntil('\n');

    yprHorizontal = MPUHorizontal.getYawPitchRoll();
    yprVertical = MPUVertical.getYawPitchRoll();

    snprintf(packet, 100, "%.2f,%.2f,%s\n", yprHorizontal[0], yprVertical[1], msg.c_str());
    // Serial.print(packet);
    UDPSendPacket(packet);
  }
  // delay(20);

  // ArduinoSerial.println("Hello from ESP32");
  // delay(1000);
}