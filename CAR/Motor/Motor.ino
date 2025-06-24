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
const unsigned long periodMotors = 5000;  //the value is a number of milliseconds
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

  digitalWrite(LeftRelayEnable, HIGH); // LOW is turn on, HIGH is turn off
  digitalWrite(RightRelayEnable, HIGH);

  delay(5000); // This is for the mpu to take time to setup
}

void loop() {
  // currentMillisMotors = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  // if (currentMillisMotors - startMillisMotors >= periodMotors)  //test whether the period has elapsed
  // {
  //   // TODO
  //   MotorRotateTo(0);. ;
  //   startMillisMotors = currentMillisMotors;  //IMPORTANT to save the start time of the current LED state.
  // }
  // MotorGoForward();
  yprCar = getYawPitchRoll();
  distanceLidar = getDistanceLidar();
  data = String(yprCar[0], 2) + "," + 
                String(yprCar[1], 2) + "," + 
                String(yprCar[2], 2) + "," +
                String(distanceLidar) + "," + 
                String(yprCar[3], 2) + "," + 
                String(yprCar[4], 2) + "," + 
                String(yprCar[5], 2);
                // "9";
  // Serial.println(data);
  Serial1.println(data);
  // FirstMems();
}