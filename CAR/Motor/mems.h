#define FIRSTMDMEMSIN1 53 // Motor Driver MEMS Input
#define FIRSTMDMEMSIN2 51

#define SECONDMDMEMSIN1 49
#define SECONDMDMEMSIN2 47

// Variables For Timing MEMS1
unsigned long startMillisMEMS1;  //some global variables available anywhere in the program
unsigned long currentMillisMEMS1;
const unsigned long periodMEMS1 = 50;  //the value is a number of milliseconds

int valueMEMS1 = HIGH;
int valueSecondMEMS1 = LOW;

// Variables For Timing MEMS2
unsigned long startMillisMEMS2;  //some global variables available anywhere in the program
unsigned long currentMillisMEMS2;
const unsigned long periodMEMS2 = 50;  //the value is a number of milliseconds

int valueMEMS2 = HIGH;
int valueSecondMEMS2 = LOW;

void SetupMems() {
  pinMode(FIRSTMDMEMSIN1, OUTPUT);
  pinMode(FIRSTMDMEMSIN2, OUTPUT);

  pinMode(SECONDMDMEMSIN1, OUTPUT);
  pinMode(SECONDMDMEMSIN2, OUTPUT);
}

void FirstMems() {
  // analogWrite(MDMEMSENB, 255);

  currentMillisMEMS1 = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillisMEMS1 - startMillisMEMS1 >= periodMEMS1)  //test whether the period has elapsed
  {
    // TODO
    digitalWrite(FIRSTMDMEMSIN1,valueMEMS1);
    digitalWrite(FIRSTMDMEMSIN2,valueSecondMEMS1);
    valueMEMS1 = (valueMEMS1 == HIGH) ? LOW : HIGH;
    valueSecondMEMS1 = (valueSecondMEMS1 == HIGH) ? LOW : HIGH;
    startMillisMEMS1 = currentMillisMEMS1;  //IMPORTANT to save the start time of the current LED state.
  }

  // digitalWrite(FIRSTMDMEMSIN1,LOW);
  // digitalWrite(FIRSTMDMEMSIN2,HIGH);
  // delay(50);
  // digitalWrite(FIRSTMDMEMSIN1,HIGH);
  // digitalWrite(FIRSTMDMEMSIN2,LOW);
  // delay(50);
}

void SecondMems() {
  // analogWrite(MDMEMSENB, 255);
  currentMillisMEMS2 = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillisMEMS2 - startMillisMEMS2 >= periodMEMS2)  //test whether the period has elapsed
  {
    // TODO
    digitalWrite(SECONDMDMEMSIN1,valueMEMS2);
    digitalWrite(SECONDMDMEMSIN2,valueSecondMEMS2);
    valueMEMS2 = (valueMEMS2 == HIGH) ? LOW : HIGH;
    valueSecondMEMS2 = (valueSecondMEMS2 == HIGH) ? LOW : HIGH;
    startMillisMEMS2 = currentMillisMEMS2;  //IMPORTANT to save the start time of the current LED state.
  }
}

void twoMems() {
  FirstMems();
  SecondMems();
}