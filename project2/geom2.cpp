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
  this->x = 0;
  this->y = 0;
  this->directionRad = 0;
  this->magnitude = 0;
}

Velocity::Velocity(int x, int y) {
  this->x = x;
  this->y = y;
  Velocity::setDirectionRad();
  Velocity::setMagnitude();
}

bool Velocity::moving(double t) {
  return (ACCELERATION * t) + magnitude >= 0;
}

// setting new x and y values will adjust the direction
// and magnitude accordingly
void Velocity::setXY(int x, int y) {
  this->x = x;
  this->y = y;
  Velocity::setDirectionRad();
  Velocity::setMagnitude();
}

// reduce the magnitude of a velocity proportional to time for
// calculating collisions
void Velocity::slow(double t) {
  magnitude += ACCELERATION * t;
  updateXY();
}

void Velocity::setDirectionRad() {
  if(x == 0) {
    if(y >= 0) {
      directionRad = 3.14159 / 2;
    } else {
      directionRad = -3.14159 / 2;
    }
  } else {
    directionRad = atan(y/x);
  }
}

void Velocity::reverse() {
  setXY(x * -1, y * -1);
}

// After slowing/reducing the magnitude, updates x and y
void Velocity::updateXY() {
  x = cos(directionRad) * magnitude;
  y = sin(directionRad) * magnitude;
}

void Velocity::scalarSelfProduct(int scalar) {
  setXY(scalar * x, scalar * y);
} 

int DotProduct(Velocity vA, Velocity vB) {
  return vA.getX() * vB.getX() + vA.getY() * vB.getY(); 
}

float AngleBetween(Velocity vA, Velocity vB) {
  return acos(DotProduct(vA, vB) / (vA.getMagnitude() * vB.getMagnitude()));
}

Velocity sumOfVelocities(Velocity vA, Velocity vB) {

  Velocity answer = Velocity( (vA.getX() + vB.getX() ), (vA.getY() + vB.getY() ));
  return answer;
  
}

Velocity scalarProduct( int scalar, Velocity v){

  Velocity answer = Velocity( (v.getX() * scalar ), (v.getY() * scalar ));
  return answer;
}

// Operator override
// Add this instance's value to other, and return a new instance
  // with the result.
Velocity Velocity::operator-(Velocity &other) {
    return Velocity(x - other.getX(), y - other.getY());
}
