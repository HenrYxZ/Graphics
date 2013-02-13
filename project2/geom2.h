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
int distance(int xA, int yA, int xB, int yB);

// computes the hypotenuse of a triangle formed by the x and y
// values of a velocity
int pythagorean(int x, int y);

// Conversion between degrees and radians
float RadtoDeg(float rad);
float DegtoRad(float deg);

// Velocity class
class Velocity {
 public:
  Velocity();
  Velocity(int x, int y);
  double getX() { return x; }
  double getY() { return y; }
  double getMagnitude() { return magnitude; }
  double getDirection() { return directionRad; }
  bool moving(double t);
  void setXY(int x, int y);
  void slow(double t);
  void reverse();
  void scalarSelfProduct(int scalar);
  void print();

  // operators
  Velocity operator-(Velocity &other);
 private:
  double x;
  double y;
  float directionRad;
  double magnitude;
  void setMagnitude() { magnitude = ALPHA * pythagorean(x, y); }
  void setDirectionRad();
  void updateXY();
};


int DotProduct(Velocity vA, Velocity vB);

// Uses the dot product between two velocity vectors to compute
// the angle between them. Returns an angle in radians.
float AngleBetween(Velocity vA, Velocity vB);

Velocity sumOfVelocities( Velocity vA, Velocity vB);
Velocity scalarProduct(double scalar, Velocity v);


#endif
