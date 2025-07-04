#include "HardwareSerial.h"
#include "Arduino.h"
#include "gyro.h"

#define FrontLeftEnable 4  //PWM Wheel
#define FrontRightEnable 5 //PWM Wheel

#define BackLeftEnable 6  //PWM Wheel
#define BackRightEnable 7 //PWM Wheel

#define FrontLeftInput2 22 //Wheel
#define FrontLeftInput1 23 //Wheel
#define FrontRightInput2 24 //Wheel
#define FrontRightInput1 25 //Wheel

#define BackLeftInput1 26 //Wheel
#define BackLeftInput2 27 //Wheel
#define BackRightInput1 28 //Wheel
#define BackRightInput2 29 //Wheel

#define BackLeftRatio 0.35 //Ratio to make all motors with the same speed

#define SizeOutput 12 // Array to make all of that is output
int arrayOutput[SizeOutput] = {FrontLeftEnable, FrontRightEnable, BackLeftEnable, BackRightEnable, FrontLeftInput1, FrontLeftInput2, FrontRightInput1, FrontRightInput2, BackLeftInput1, BackLeftInput2, BackRightInput1, BackRightInput2};

void SetupMotorPower(int valueOfPower) {
  analogWrite(FrontLeftEnable, valueOfPower); // To make all motors run on valueOfPower power
  analogWrite(FrontRightEnable, valueOfPower);
  analogWrite(BackLeftEnable, valueOfPower * BackLeftRatio);
  analogWrite(BackRightEnable, valueOfPower);
}

void SetupMotors() {
  for(int i = 0; i < SizeOutput; i++) {
    pinMode(arrayOutput[i], OUTPUT); // Make all of the variable in the array as output
  }

  SetupMotorPower(255); // to adjust power of motors
  SetupGyro();
}

void MotorSteady() {
  digitalWrite(FrontLeftInput1, LOW);
  digitalWrite(FrontLeftInput2, LOW);

  digitalWrite(FrontRightInput1, LOW);
  digitalWrite(FrontRightInput2, LOW);

  digitalWrite(BackLeftInput1, LOW);
  digitalWrite(BackLeftInput2, LOW);

  digitalWrite(BackRightInput1, LOW);
  digitalWrite(BackRightInput2, LOW);
}

void MotorGoForward() {
  digitalWrite(FrontLeftInput1, LOW);
  digitalWrite(FrontLeftInput2, HIGH);

  digitalWrite(FrontRightInput1, LOW);
  digitalWrite(FrontRightInput2, HIGH);

  digitalWrite(BackLeftInput1, HIGH);
  digitalWrite(BackLeftInput2, LOW);

  digitalWrite(BackRightInput1, HIGH);
  digitalWrite(BackRightInput2, LOW);
}

void MotorGoBackward() {
  digitalWrite(FrontLeftInput1, HIGH);
  digitalWrite(FrontLeftInput2, LOW);

  digitalWrite(FrontRightInput1, HIGH);
  digitalWrite(FrontRightInput2, LOW);

  digitalWrite(BackLeftInput1, LOW);
  digitalWrite(BackLeftInput2, HIGH);

  digitalWrite(BackRightInput1, LOW);
  digitalWrite(BackRightInput2, HIGH);
}

void MotorGoRight() {
  digitalWrite(FrontLeftInput1, LOW);
  digitalWrite(FrontLeftInput2, HIGH);

  digitalWrite(FrontRightInput1, HIGH);
  digitalWrite(FrontRightInput2, LOW);

  digitalWrite(BackLeftInput1, LOW);
  digitalWrite(BackLeftInput2, HIGH);

  digitalWrite(BackRightInput1, HIGH);
  digitalWrite(BackRightInput2, LOW);
}

void MotorGoLeft() {
  digitalWrite(FrontLeftInput1, HIGH);
  digitalWrite(FrontLeftInput2, LOW);

  digitalWrite(FrontRightInput1, LOW);
  digitalWrite(FrontRightInput2, HIGH);

  digitalWrite(BackLeftInput1, HIGH);
  digitalWrite(BackLeftInput2, LOW);

  digitalWrite(BackRightInput1, LOW);
  digitalWrite(BackRightInput2, HIGH);
}

void MotorRotateRight() {
  digitalWrite(FrontLeftInput1, LOW);
  digitalWrite(FrontLeftInput2, HIGH);

  digitalWrite(FrontRightInput1, HIGH);
  digitalWrite(FrontRightInput2, LOW);

  digitalWrite(BackLeftInput1, HIGH);
  digitalWrite(BackLeftInput2, LOW);

  digitalWrite(BackRightInput1, LOW);
  digitalWrite(BackRightInput2, HIGH);
}

void MotorRotateLeft() {
  digitalWrite(FrontLeftInput1, HIGH);
  digitalWrite(FrontLeftInput2, LOW);

  digitalWrite(FrontRightInput1, LOW);
  digitalWrite(FrontRightInput2, HIGH);

  digitalWrite(BackLeftInput1, LOW);
  digitalWrite(BackLeftInput2, HIGH);

  digitalWrite(BackRightInput1, HIGH);
  digitalWrite(BackRightInput2, LOW);
}

// The value between 0 - 359
void MotorRotateTo(float degreeValue) {
  MotorSteady();
  SetupMotorPower(100);
  float *yawPitchRoll = new float[3];
  yawPitchRoll = getYawPitchRoll();
  auto minus = [](float &value) -> void {
    if(value < 0) {
      value += 360;
    }
  };

  // Claculate distance from left and right to compare whose nearest
  float yaw = yawPitchRoll[0];
  minus(yaw);
  float distanceLeft = yaw - degreeValue;
  minus(distanceLeft);
  float distanceRight = degreeValue - yaw;
  minus(distanceRight);

  // Serial.print("Right ------> ");
  // Serial.print(distanceRight);
  // Serial.print("\t distance left <------ ");
  // Serial.println(distanceLeft);

  // This is for detect left or right
  if(distanceLeft < distanceRight) {
    if (distanceLeft > 6) { // Error percentage
      MotorRotateLeft();
      distanceLeft = yaw - degreeValue;
      minus(distanceLeft);
      SetupMotorPower(max(distanceLeft, 40)); // To adjust the speed of rotate
    } else {
        MotorSteady();
    }
  } else {
    if(distanceRight > 6) {
      MotorRotateRight();
      distanceRight = degreeValue - yaw;
      minus(distanceRight);
      SetupMotorPower(max(distanceRight, 40));
    } else {
      MotorSteady();
    }
  }
  SetupMotorPower(255);
}