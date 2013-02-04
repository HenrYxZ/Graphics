#ifndef __BALL_H__
#define __BALL_H__

#include "./geom2.h"

#define BALL_RADIUS 10

enum Color { WHITE, BLACK, RED, GREEN, BLUE }; 

// A handy Ball class
class Ball {

public:
  // the current position of the ball
  int x, y;

  // the color of the ball as defined by the color enumeration
  Color color;

  struct velocity {
    int x;
    int y;
  } velocity;

  Ball();

  Ball(int x, int y, Color color);

};

#endif
