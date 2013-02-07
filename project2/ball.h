#ifndef __BALL_H__
#define __BALL_H__

#include "./geom2.h"

#define BALL_RADIUS 10
#define FRICTION 0.5

// the following four definitions specify the boundary of the four walls
#define TOP_WALL 200
#define BOTTOM_WALL -200
#define RIGHT_WALL 150
#define LEFT_WALL -150

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

  // moves the ball along based on how much time
  // has elapsed since it's been moved and the current velocity
  // also slows it down based on the friction coefficient
  // as defined above and
  // returns true if it moved, false if not
  bool move();

  // checks for collision with the other ball, then updates
  // the velocity vector accordingly if a collision has occured
  // it then returns true if a collision has occured, and false if not
  bool collide(Ball other);

  // checks for collision with the walls as defined above
  // then updates the velocity vector accordingly if a collision
  // has occured and returns true if an update happened and false if not
  bool collideWithWall();
};

#endif
