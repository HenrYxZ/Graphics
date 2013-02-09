#include <iostream>
#include "./ball.h"

// Handy ball class implementation

using namespace std;

Ball::Ball() {
  this->x = 0;
  this->y = 0;
  this->color = WHITE;
  this->velocity = Velocity();
}

Ball::Ball(int x, int y, Color color) {
  this->x = x;
  this->y = y;
  this->color = color;
  this->velocity = Velocity();
}

bool Ball::move() {
  // TODO: implement
  if(velocity.getMagnitude() <= 0) {
    return false;
  }
  // debug spew to ensure correct functionality
  cout << "Ball at (" << x << ", " << y << ") moved.\n";

  return false;
}

bool Ball::collide(Ball other) {
  bool hasCollided = false;

 
  // first, we need to check for a collision.
  if (distance(x, y, other.x, other.y) <= (BALL_RADIUS * 2)) {
    hasCollided = true;
  }

  if (hasCollided) {
    // TODO: simulate a collision by updating the velocity vectors according
    // to the laws of physics.
    // debug spew to ensure correct functionality
    cout << "Ball at (" << x << ", " << y << ") has collided with " <<
    "Ball at (" << other.x << ", " << other.y << ")\n"; 
    /*The equation is x_1²+x_2² = x_0²
    and x_1+x_2 = x_0 for speed
    */

  }

  return hasCollided;
}

bool Ball::collideWithWall() {
  bool hasCollided = false;

  

  if ((x <= LEFT_WALL) || (x >= RIGHT_WALL) ||
    (y <= BOTTOM_WALL) || (y >= TOP_WALL)) {
    hasCollided = true;
  }

  if (hasCollided) {

    // debug spew to ensure correct functinality
  cout << "Ball at (" << x << ", " << y << ") has collided with a wall\n";
    
    // TODO: handle collision with a wall by reflecting the current velocity vector
    // across the normal to the wall it collided with and reversing its direction
  }

  return hasCollided;
}
