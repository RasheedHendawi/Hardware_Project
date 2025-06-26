#include <Arduino.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "gyro.h"
#include "udpConnection.h"
#include "HardwareSerial.h"
#include "odom.h"

HardwareSerial ArduinoSerial(2); // Use UART1 on ESP32

MPUClass MPUHorizontal(1);
MPUClass MPUVertical(2);
float* yprHorizontal, *yprVertical;
char packet[100];
float theta = 0;

void setup() {
  Serial.begin(115200);

  SetupOdom();

  MPUHorizontal.SetupGyro();

  MPUVertical.SetupGyro();

  UDPSetup();

  ArduinoSerial.begin(115200, SERIAL_8N1, 16, 17);  // RX=3, TX=1

  // delay(5000);
}

void loop() {
  if (ArduinoSerial.available()) {
    String msg = ArduinoSerial.readStringUntil('\n');
    // Serial.println(msg);
    
    // std::string yawString = "";
    // for(int i = 0; i < msg.length(); i++) {
    //   if(msg[i] == ',') {
    //     break;
    //   }
    //   yawString.push_back(msg[i]);
    // }
    // theta = std::stof(yawString);
    // Serial.print("Theeeeeeeeeeeeeeta is: ");
    // Serial.println(theta);

    yprHorizontal = MPUHorizontal.getYawPitchRoll();
    yprVertical = MPUVertical.getYawPitchRoll();

    snprintf(packet, 100, "%.2f,%.2f,%s,%f\n", yprHorizontal[0], yprVertical[1], msg.c_str(), getVelocity());
    // Serial.print(packet);
    UDPSendPacket(packet);
  }
  // ReadOdom();
  // Serial.print("The Distance is: ");
  // Serial.println(getDistance());
  // Serial.print("The Velocity is: ");
  // Serial.println(getVelocity());
  // delay(20);

  // ArduinoSerial.println("Hello from ESP32");
  // delay(1000);
}