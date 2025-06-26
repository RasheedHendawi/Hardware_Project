#include "motor.h"
#include "mems.h"
#include "ultrasonic.h"
#include "lidar.h"
#include "laser.h"

// Begin Declare Pins
#define LeftRelayEnable 2  //MOTORS
#define RightRelayEnable 3 //MEMS
// End Declare Pins

// Begin Declare Variables
// Variables For Timing
unsigned long startMillisMotors;  //some global variables available anywhere in the program
unsigned long currentMillisMotors;
const unsigned long periodMotors = 3000;  //the value is a number of milliseconds
int who = 0;
// bool flagDirectionForwardBackward = false; // To make it goes Forward and Backward ulternative

String data;
float *yprCar;
int distanceLidar;
// End Declare Variables

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  // Begin Laser Setup
  SetupLaser();
  LaserStatus(1);

  // Begin Lidar Setup
  SetupLidar();
  Serial.println("Hello");

  // Begin Motor Setup
  SetupMotors();

  // Begin MEMS Setup
  SetupMems();

  // Staff Setup
  pinMode(LeftRelayEnable, OUTPUT);
  pinMode(RightRelayEnable, OUTPUT);

  delay(10000); // This is for the mpu to take time to setup

  digitalWrite(LeftRelayEnable, LOW); // LOW is turn on, HIGH is turn off
  digitalWrite(RightRelayEnable, LOW);
}

void loop() {
  MotorSteady();
  // currentMillisMotors = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  // if (currentMillisMotors - startMillisMotors >= periodMotors)  //test whether the period has elapsed
  // {
  //   // TODO
  //   if(who < 8) {
  //     who++;
  //   }
  //   startMillisMotors = currentMillisMotors;  //IMPORTANT to save the start time of the current LED state.
  // }
  // switch(who) {
  //   case 0:
  //   case 1:
  //     MotorSteady();
  //     break;
  //   case 2:
  //     MotorGoForward();
  //   break;
  //   case 3:
  //     MotorSteady();
  //   break;
  //   case 4:
  //     MotorRotateTo(180);
  //     // MotorRotateLeft();
  //   break;
  //   case 5:
  //     MotorGoForward();
  //   break;
  //   case 6:
  //     MotorSteady();
  //   break;
  //   case 7:
  //     MotorRotateTo(0);
  //   break;
  //   case 8:
  //     MotorSteady();
  //   break;
  // }
  // MotorRotateLeft();
  yprCar = getYawPitchRoll();
  distanceLidar = getDistanceLidar();
  data = String(yprCar[0], 4) + "," + 
                String(yprCar[1], 4) + "," + 
                String(yprCar[2], 4) + "," +
                String(distanceLidar) + "," + 
                String(mpu.getZGyroOffset(), 4);
                // "9";
  Serial1.println(data);
  // Serial.println(data);
  twoMems();
}