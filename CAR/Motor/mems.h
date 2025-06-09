#define FIRSTMDMEMSIN1 53 // Motor Driver MEMS Input
#define FIRSTMDMEMSIN2 51

#define SECONDMDMEMSIN1 49
#define SECONDMDMEMSIN2 47

void SetupMems() {
  pinMode(FIRSTMDMEMSIN1, OUTPUT);
  pinMode(FIRSTMDMEMSIN2, OUTPUT);

  pinMode(SECONDMDMEMSIN1, OUTPUT);
  pinMode(SECONDMDMEMSIN2, OUTPUT);
}

void FirstMems() {
  // analogWrite(MDMEMSENB, 255);
  digitalWrite(FIRSTMDMEMSIN1,LOW);
  digitalWrite(FIRSTMDMEMSIN2,HIGH);
  delay(50);
  digitalWrite(FIRSTMDMEMSIN1,HIGH);
  digitalWrite(FIRSTMDMEMSIN2,LOW);
  delay(50);
}

void SecondMems() {
  // analogWrite(MDMEMSENB, 255);
  digitalWrite(SECONDMDMEMSIN1,LOW);
  digitalWrite(SECONDMDMEMSIN2,HIGH);
  delay(50);
  digitalWrite(SECONDMDMEMSIN1,HIGH);
  digitalWrite(SECONDMDMEMSIN2,LOW);
  delay(50);
}