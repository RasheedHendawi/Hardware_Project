#include <Ultrasonic.h>

 // ultrasonic(Trig, Echo);
Ultrasonic ultrasonicFront(30, 31); // For the front ultrasonic

int getDistanceFrontUltrasonic() {
  return ultrasonicFront.read();
}
