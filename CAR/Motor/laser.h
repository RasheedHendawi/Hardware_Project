#define LaserGND 32
#define LaserVCC 33
#define LaserEnable 34

void SetupLaser() {
  pinMode(LaserGND, OUTPUT);
  pinMode(LaserVCC, OUTPUT);
  pinMode(LaserEnable, OUTPUT);
  digitalWrite(LaserGND, LOW);
  digitalWrite(LaserVCC, HIGH);
}

void LaserStatus(int state) {
  if(state == 0) {
      digitalWrite(LaserEnable, LOW);
  } else if(state == 1) {
      digitalWrite(LaserEnable, HIGH);
  }
}