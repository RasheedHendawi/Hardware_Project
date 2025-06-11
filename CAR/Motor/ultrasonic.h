#include <Ultrasonic.h>

 // ultrasonic(Trig, Echo);
Ultrasonic ultrasonicFront(34, 35); // For the front ultrasonic

int getDistanceFrontUltrasonic() {
  return ultrasonicFront.read();
}
