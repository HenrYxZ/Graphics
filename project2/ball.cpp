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

bool Ball::move() {
  // not implemented yet
  return false;
}

bool Ball::collide(Ball other) {
  bool hasCollided = false;

  // first, we need to check for a collision.
  if (distance(x, y, other.x, other.y) <= (BALL_RADIUS * 2)) {
    hasCollided = true;
  }

  if (hasCollided) {
    // simulate a collision by updating the velocity vectors according
    // to the laws of physics.
  }

  return hasCollided;
}
