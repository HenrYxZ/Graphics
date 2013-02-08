#include <math.h>

#ifndef __GEOM2_H__
#define __GEOM2_H__

// Alpha value used for determining initial magnitude
#define ALPHA 1

// Arbitrary value for acceleration of balls in motion
#define ACCELERATION -5

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
  int getX() { return x; }
  int getY() { return y; }
  int getMagnitude() { return magnitude; }
  bool moving() { return (magnitude > 0); }
  void setXY(int x, int y);
  void slow(int t);
 private:
  int x;
  int y;
  float directionRad;
  int magnitude;
  void setMagnitude() { magnitude = ALPHA * pythagorean(x, y); }
  void setDirectionRad() { directionRad = atan(y/x); }
  void updateXY();
};


int DotProduct(Velocity vA, Velocity vB);

// Uses the dot product between two velocity vectors to compute
// the angle between them. Returns an angle in radians.
float AngleBetween(Velocity vA, Velocity vB);


#endif
