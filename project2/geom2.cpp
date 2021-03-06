#include "./geom2.h"

double distance(double xA, double yA, double xB, double yB) {
  return sqrt(pow((xB - xA), 2) + pow((yB - yA), 2));
}

double pythagorean(double x, double y) {
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

Velocity::Velocity(double x, double y) {
  this->x = x;
  this->y = y;
  setDirectionRad();
  setMagnitude();
}

bool Velocity::moving(double t) {
  return ACCELERATION * t + magnitude >= 0;
}

// setting new x and y values will adjust the direction
// and magnitude accordingly
void Velocity::setXY(double x, double y) {
  this->x = x;
  this->y = y;
  setDirectionRad();
  setMagnitude();
}

// reduce the magnitude of a velocity proportional to time for
// calculating collisions
void Velocity::slow(double t) {
  // check for rollovers and set 0 if one occurs
  if (x > 0) {
    x += ACCELERATION * t;

    if (x < 0) {
      x = 0;
    }
  } else {
    x -= ACCELERATION * t;

    if (x > 0) {
      x = 0;
    }
  }

  // do the same for y
  if (y > 0) {
    y += ACCELERATION * t;

    if (y < 0) {
      y = 0;
    }
  } else {
    y -= ACCELERATION * t;

    if (y > 0) {
      y = 0;
    }
  }

  // update our member variables
  setMagnitude();
  setDirectionRad();
}

void Velocity::setDirectionRad() {
  if (this->x == 0) {
    if (this->y >= 0) {
      directionRad = 3.14159 / 2;
    } else {
      directionRad = -3.14159 / 2;
    }
  } else {
    directionRad = atan(static_cast<double>(y/x));
  }
}

void Velocity::reverse() {
  setXY(x * -1, y * -1);
}

void Velocity::scalarSelfProduct(double scalar) {
  setXY(scalar * x, scalar * y);
}

void Velocity::print() {
  cout << "[" << x << ", " << y << "] with magnitude of " <<
    magnitude << " and degree of " << directionRad << "\n";
}

double DotProduct(Velocity vA, Velocity vB) {
  return vA.getX() * vB.getX() + vA.getY() * vB.getY();
}

float AngleBetween(Velocity vA, Velocity vB) {
  return acos(DotProduct(vA, vB) / (vA.getMagnitude() * vB.getMagnitude()));
}

Velocity sumOfVelocities(Velocity vA, Velocity vB) {
  Velocity answer = Velocity((vA.getX() + vB.getX()), (vA.getY() + vB.getY()));
  return answer;
}

Velocity scalarProduct(double scalar, Velocity v) {
  Velocity answer = Velocity((v.getX() * scalar), (v.getY() * scalar));
  return answer;
}

// Operator override
// Add this instance's value to other, and return a new instance
  // with the result.
Velocity Velocity::operator-(const Velocity &other) {
    return Velocity(x - other.x, y - other.y);
}
