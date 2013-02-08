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



// Velocity class
class Velocity {
 public:
  Velocity() {}
  int getX() { return x; }
  int getY() { return y; }
  float getMagnitude() { return magnitude; }
  void setXY(int x, int y);
  bool moving() { return (magnitude > 0); }
  void slow(int t) { magnitude += ACCELERATION * t; }
 private:
  int x;
  int y;
  float directionRad;
  float magnitude;
  void updateMagnitude() { magnitude = ALPHA * pythagorean(x, y); }
  void setDirectionRad() { directionRad = atan(y/x); }
};

// Uses the dot product between two velocity vectors to compute
// the angle between them. Returns an angle in radians.
float DotProduct(Velocity vA, Velocity vB);


#endif
