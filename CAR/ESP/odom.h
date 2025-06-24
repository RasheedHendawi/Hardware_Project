#include "esp32-hal-gpio.h"
#include <utility>
#define encoderPin 4

volatile int holeCount = 0;
volatile unsigned long lastInterruptTime = 0;
unsigned long lastVelocityTime = 0;
double lastDistanceVelocity = 0;
double lastDistanceXY = 0;
double X = 0, Y = 0;

const double holeNumber = 20;
const double diameter = 0.025; // in meter
const double perimeter = diameter * 3.141592654;

void countHoles() {
  unsigned long currentTime = micros();  // microseconds for better resolution
  if (currentTime - lastInterruptTime >= 10000) {  // 1000us = 1ms
    holeCount++;
    lastInterruptTime = currentTime;
  }
}

void SetupOdom() {
  pinMode(encoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPin), countHoles, FALLING);
}

void ReadOdom() {
  Serial.print("Holes Passed: ");
  Serial.println(holeCount);
  delay(500);  // Update every half second
}

double getDistance() {
  double numberOfRevolution = holeCount / holeNumber;
  double distance = numberOfRevolution * perimeter; // in meter
  return distance;
}

double getVelocity() {
  unsigned long currentTime = millis();
  double time = currentTime - lastVelocityTime;
  lastVelocityTime = currentTime;
  time /= 1000;
  double distance = getDistance();
  double currentDistance = distance - lastDistanceVelocity;
  lastDistanceVelocity = distance;
  return currentDistance / time;
}

std::pair<double, double> getXY(float theta) {
  // x += v * cos(theta) * Δt;
  // y += v * sin(theta) * Δt;
  double distance = getDistance();
  double currentDistance = distance - lastDistanceXY;
  lastDistanceXY = distance;
  X += currentDistance * cos(theta);
  Y += currentDistance * sin(theta);
}