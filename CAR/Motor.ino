#include "motor.h"
#include "mems.h"

// Begin Declare Pins
#define LeftRelayEnable 2  //MOTORS
#define RightRelayEnable 3 //MEMS
// End Declare Pins

// Begin Declare Variables
// Variables For Timing
unsigned long startMillisMotors;  //some global variables available anywhere in the program
unsigned long currentMillisMotors;
const unsigned long periodMotors = 6000;  //the value is a number of milliseconds
// bool flagDirectionForwardBackward = false; // To make it goes Forward and Backward ulternative
// End Declare Variables

void setup() {
  Serial.begin(115200);

  // Begin Motor Setup
  SetupMotors();

  // Begin MEMS Setup
  SetupMems();

  // Staff Setup
  pinMode(LeftRelayEnable, OUTPUT);
  pinMode(RightRelayEnable, OUTPUT);

  digitalWrite(LeftRelayEnable, LOW); // LOW is turn on, HIGH is turn off
  digitalWrite(RightRelayEnable, HIGH);

  delay(5000); // This is for the mpu to take time to setup
}

void loop() {
  currentMillisMotors = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillisMotors - startMillisMotors >= periodMotors)  //test whether the period has elapsed
  {
    // TODO
    MotorRotateTo(0);
    startMillisMotors = currentMillisMotors;  //IMPORTANT to save the start time of the current LED state.
  }
  // FirstMems();
}
