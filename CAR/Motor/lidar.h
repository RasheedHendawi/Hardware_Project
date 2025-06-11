#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

void SetupLidar() {
  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  myLidarLite.configure(0); // Change this number to try out alternate configurations
}

int getDistanceLidar() {
  return myLidarLite.distance();
}