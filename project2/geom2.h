#include <math.h>
#include <iostream>

#ifndef __GEOM2_H__
#define __GEOM2_H__

// Alpha value used for determining initial magnitude
#define ALPHA 1

// Arbitrary value for acceleration of balls in motion
#define ACCELERATION -100

// Maximum speed per ball
#define MAX_SPEED 200

using namespace std;

// Handy geometry classes and functions

// computes the distance between two two-dimensional points
double distance(double xA, double yA, double xB, double yB);

// computes the hypotenuse of a triangle formed by the x and y
// values of a velocity
double pythagorean(double x, double y);

// Conversion between degrees and radians
float RadtoDeg(float rad);
float DegtoRad(float deg);

// Velocity class
class Velocity {
 public:
  double x;
  double y;
  Velocity();
  Velocity(double x, double y);
  double getX() { return x; }
  double getY() { return y; }
  double getMagnitude() { return magnitude; }
  double getDirection() { return directionRad; }
  bool moving(double t);
  void setXY(double x, double y);
  void slow(double t);
  void reverse();
  void scalarSelfProduct(double scalar);
  void print();

  // operators
  Velocity operator-(const Velocity &other);

 private:
  float directionRad;
  double magnitude;
  void setMagnitude() { magnitude = ALPHA * pythagorean(x, y); }
  void setDirectionRad();
  void updateXY();
};


double DotProduct(Velocity vA, Velocity vB);

// Uses the dot product between two velocity vectors to compute
// the angle between them. Returns an angle in radians.
float AngleBetween(Velocity vA, Velocity vB);

Velocity sumOfVelocities(Velocity vA, Velocity vB);
Velocity scalarProduct(double scalar, Velocity v);


#endif
