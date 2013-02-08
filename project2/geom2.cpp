#include "./geom2.h"

int distance(int xA, int yA, int xB, int yB) {
  return sqrt(pow((xB - xA), 2) + pow((yB - yA), 2));
}

int pythagorean(int x, int y) {
  return sqrt(pow(x, 2) + pow(y, 2));
}

float RadtoDeg(float rad) {
  return rad * 180 / 3.14159;
}

float DegtoRad(float deg) {
  return deg * 3.14159 / 180;
}

Velocity::Velocity() {
  this->x = 1;
  this->y = 1;
  Velocity::setDirectionRad();
  Velocity::setMagnitude();
}

Velocity::Velocity(int x, int y) {
  this->x = x;
  this->y = y;
  Velocity::setDirectionRad();
  Velocity::setMagnitude();
}

// setting new x and y values will adjust the direction
// and magnitude accordingly
void Velocity::setXY(int x, int y) {
  this->x = x;
  this->y = y;
  Velocity::setDirectionRad();
  Velocity::setMagnitude();
}

void Velocity::slow(int t) {
  magnitude += ACCELERATION * t;
  updateXY();
}

// After slowing/reducing the magnitude, updates x and y
void Velocity::updateXY() {
  x = cos(directionRad) * magnitude;
  y = sin(directionRad) * magnitude;
}

int DotProduct(Velocity vA, Velocity vB) {
  return vA.getX() + vA.getY() + vB.getX() + vB.getY(); 
}

float AngleBetween(Velocity vA, Velocity vB) {
  return acos(DotProduct(vA, vB) / (vA.getMagnitude() * vB.getMagnitude()));
}
