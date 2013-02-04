#include "./ball.h"

// Handy ball class implementation

Ball::Ball() {
  this->x = 0;
  this->y = 0;
  this->color = WHITE;
}

Ball::Ball(int x, int y, Color color) {
  this->x = x;
  this->y = y;
  this->color = color;
}
