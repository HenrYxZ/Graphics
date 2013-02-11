#include <iostream>
#include "./ball.h"

// Handy ball class implementation

using namespace std;

Ball::Ball() {
  this->x = 0;
  this->y = 0;
  x_0 = 0;
  y_0 = 0;
  velocityChanged = false;
  this->color = WHITE;
  this->velocity = Velocity();
}

Ball::Ball(int x, int y, Color color) {
  this->x = x;
  this->y = y;
  x_0 = x;
  y_0 = y;
  velocityChanged = false;
  this->color = color;
  this->velocity = Velocity();
}

bool Ball::move(int t) {
  // TODO: implement
  if(velocity.getMagnitude() <= 0) {
    return false;
  }
  // Elapsed time in seconds
  elapsedTime = (double)(t - moveStartTime) / 1000;

  // Update position according to elapsed time
  x = (0.5 * ACCELERATION * elapsedTime * elapsedTime)
        * (velocity.getX() / velocity.getMagnitude())
        + (velocity.getX() * elapsedTime) + x_0;
  y = (0.5 * ACCELERATION * elapsedTime * elapsedTime)
        * (velocity.getY() / velocity.getMagnitude())
        + (-1 * velocity.getY() * elapsedTime) + y_0;

  if(!velocity.moving(elapsedTime)) {
    velocity.slow(elapsedTime);
    x_0 = x;
    y_0 = y;
  }

  // debug spew to ensure correct functionality
  // cout << "Ball at (" << x << ", " << y << ") moved
  //cout << "Magnitude: " << velocity.getMagnitude() << "\n";
  //cout << "Elapsed Time: " << elapsedTime << "\n";
  //cout << "Vx = " << velocity.getX() << ", Vy = " << velocity.getY() << "\n";
  //cout << "Moving(): " << velocity.moving(elapsedTime) << "\n";
  //cout << "A * t = " << (ACCELERATION * elapsedTime) << "\n";

  return true;
}

bool Ball::collide(Ball* other) {
  bool hasCollided = false;
  
  // first, we need to check for a collision.
  if (distance(x, y, other->x, other->y) <= (BALL_RADIUS * 2)) {
    hasCollided = true;
  } else {
    velocityChanged = false;
  }

  // Lots of commented tests
  if (hasCollided && !velocityChanged) {

    // TODO: simulate a collision by updating the velocity vectors according
    // to the laws of physics.
    // debug spew to ensure correct functionality
    // cout << "Ball at (" << x << ", " << y << ") has collided with " <<
    // "Ball at (" << other.x << ", " << other.y << ")\n"; 


    cout << "Ball at (" << x << ", " << y << ") has collided with " <<
   "Ball at (" << other->x << ", " << other->y << ")\n"; 

    velocityChanged = true;
/*
    // change the ball's velocity vector to match what it would be at
    // time of collision
    moveStartTime += elapsedTime * 1000;
    x_0 = x;
    y_0 = y;
    velocity.slow(elapsedTime);
    

    // alter the other ball's velocity vector
    other.moveStartTime = moveStartTime;
    other.x_0 = other.x;
    other.y_0 = other.y;
    other.velocity.slow(other.elapsedTime);
*/
    /*The equation is x_1²+x_2² = x_0²
    and x_1+x_2 = x_0 for speed
    */

    /* This are not real velocities, are vectors but I will use it 
     to use the velocity functions in geom2 */

    Velocity r1 = Velocity(velocity.getX(), velocity.getY());
    Velocity r2 = Velocity(other->velocity.getX(), other->velocity.getY());
    double absoluteV = sqrt(DotProduct(r1 - r2, r1 - r2));


    //Normal plane

    Velocity n = scalarProduct(pow(absoluteV, -1), r1 - r2);
    Velocity negativen = scalarProduct(-1, n);

    //Normal Velocities

    
    Velocity vn1 = scalarProduct( DotProduct( this->velocity, negativen ), negativen );
    Velocity vn2 = scalarProduct( DotProduct( other->velocity, n) , n);

    //tangent velocities

    Velocity vt1 = sumOfVelocities( vn1, (scalarProduct(-1, this->velocity ) ) );
    Velocity vt2 = sumOfVelocities( vn2, (scalarProduct(-1, other->velocity ) ) );

    //final velocities
    Velocity vf1 = sumOfVelocities( vt1 , vn2);
    Velocity vf2 = sumOfVelocities( vt2, vn1);

    this->velocity = vf1;
    other->velocity = vf2;

/*
    int t = (elapsedTime * 1000) + moveStartTime;

    //other->x = 0;
    //other->y = 0;
    other->x_0 = other->x;
    other->y_0 = other->y;
    other->velocity.setXY(velocity.getX(), velocity.getY());
    other->setStartTime(t);

    velocity.setXY(0, 0);
    setStartTime(t);

*/

    //other->move(t);
    //move(t);

//    cout << "Other magnitude: " << other.velocity.getMagnitude() << "\n";
   
/*
    // change the ball's velocity vector to match what it would be at
    // time of collision
    moveStartTime += elapsedTime * 1000;
    x_0 = x;
    y_0 = y;
    //velocity.slow(elapsedTime);


    // alter the other ball's velocity vector
    other->moveStartTime = moveStartTime;
    other->x_0 = other->x;
    other->y_0 = other->y;
    //other.velocity.slow(other.elapsedTime);
*/

  }

  return hasCollided;
}

bool Ball::collideWithWall() {
  bool hasCollided = false;

  if ((x <= LEFT_WALL + BALL_RADIUS) || (x >= RIGHT_WALL - BALL_RADIUS) ||
    (y <= BOTTOM_WALL + BALL_RADIUS) || (y >= TOP_WALL - BALL_RADIUS)) {
    hasCollided = true;
  }

  if (hasCollided) {

    // debug spew to ensure correct functinality
    // cout << "Ball at (" << x << ", " << y << ") has collided with a wall\n";

    // change the ball's velocity vector to match what it would be at
    // time of collision
    moveStartTime += elapsedTime * 1000;
    x_0 = x;
    y_0 = y;
    velocity.slow(elapsedTime);
    

    // handle collision with a wall by reflecting the current velocity vector
    // across the normal to the wall it collided with and reversing its direction
    // this ends up being trivial since we're reflecting across the axis' 
    if (x <= LEFT_WALL + BALL_RADIUS) {
      if (velocity.getX() < 0) {
        // reflect across y axis
        velocity.setXY(velocity.getX() * -1, velocity.getY());
      }
    } else if (x >= RIGHT_WALL - BALL_RADIUS) {
      if (velocity.getX() > 0) {
        velocity.setXY(velocity.getX() * -1, velocity.getY());
      }
    } else if (y <= BOTTOM_WALL + BALL_RADIUS) {
      if (velocity.getY() > 0) {
        // reflect across x axis
        velocity.setXY(velocity.getX(), velocity.getY() * -1);
      }
    } else {
      if (velocity.getY() < 0) {
        // then it must be a collision with the top wall
        velocity.setXY(velocity.getX(), velocity.getY() * -1);
      }
    }
  }

   return hasCollided;
}
