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
  if (velocity.getMagnitude() <= 0) {
    return false;
  }

  // Elapsed time in seconds
  elapsedTime = static_cast<double>((t - moveStartTime)) /
    static_cast<double>(1000);

  // Update position according to elapsed time
  x = (0.5 * ACCELERATION * elapsedTime * elapsedTime)
        * (velocity.getX() / velocity.getMagnitude())
        + (velocity.getX() * elapsedTime) + x_0;
  y = (0.5 * ACCELERATION * elapsedTime * elapsedTime)
        * (velocity.getY() / velocity.getMagnitude())
        + (velocity.getY() * elapsedTime) + y_0;

  if (!velocity.moving(elapsedTime)) {
    velocity.slow(elapsedTime);
    x_0 = x;
    y_0 = y;
  }

  return true;
}

bool Ball::collide(Ball* other) {
  bool hasCollided = false;

  // first, we need to check for a collision.
  if (distance(x, y, other->x, other->y) <
    static_cast<double>((BALL_RADIUS * 2))) {
    hasCollided = true;
  }

  // Lots of commented tests
  if (hasCollided) {
    // simulate a collision by updating the velocity vectors according
    // to the laws of physics.

    // Move the two balls at least 10 away from each other
    {
      Velocity r1 = Velocity(x, y);
      Velocity r2 = Velocity(other->x, other->y);
      Velocity Normal = r1 - r2;

      double ScaleToTen = static_cast<double>(-21) /
        static_cast<double>(Normal.getMagnitude());

      Normal = scalarProduct(ScaleToTen, Normal);

      // lastly, move the other ball away
      other->x = x + Normal.getX();
      other->y = y + Normal.getY();
    }

    /* The equation is x_1²+x_2² = x_0²
     *  and x_1+x_2 = x_0 for speed
     */

    /* This are not real velocities, are vectors but I will use it 
     to use the velocity functions in geom2 */
    Velocity r1 = Velocity(x, y);
    Velocity r2 = Velocity(other->x, other->y);
    double absoluteV = sqrt(DotProduct(r1 - r2, r1 - r2));

    // Normal plane
    cout << pow(absoluteV, -1) << endl;
    Velocity n = scalarProduct(pow(absoluteV, -1), r1 - r2);
    Velocity negativen = scalarProduct(-1, n);

    // Normal Velocities
    Velocity vn1 = scalarProduct(DotProduct(this->velocity, negativen),
      negativen);
    Velocity vn2 = scalarProduct(DotProduct(other->velocity, n), n);

    // tangent velocities
    Velocity vt1 = sumOfVelocities(vn1, (scalarProduct(-1, this->velocity)));
    Velocity vt2 = sumOfVelocities(vn2, (scalarProduct(-1, other->velocity)));

    // final velocities
    Velocity vf1 = sumOfVelocities(vt1, vn2);
    Velocity vf2 = sumOfVelocities(vt2, vn1);

    this->velocity = vf1;
    other->velocity = vf2;

    vf1.print();
    vf2.print();

    // change the ball's velocity vector to match what it would be at
    // time of collision
    moveStartTime += elapsedTime * 1000;
    x_0 = x;
    y_0 = y;
    velocity.slow(elapsedTime);


    // alter the other ball's velocity vector
    other->moveStartTime = moveStartTime;
    other->x_0 = other->x;
    other->y_0 = other->y;
    other->velocity.slow(other->elapsedTime);
  }

  return hasCollided;
}

bool Ball::collideWithWall() {
  bool hasCollided = false;

  if ((x < LEFT_WALL + BALL_RADIUS) || (x > RIGHT_WALL - BALL_RADIUS) ||
    (y < BOTTOM_WALL + BALL_RADIUS) || (y > TOP_WALL - BALL_RADIUS)) {
    hasCollided = true;
  }

  if (hasCollided) {
    // handle collision with a wall by reflecting the current velocity vector
    // across the normal to the wall it collided with and reverse its direction
    // this ends up being trivial since we're reflecting across the axis
    if (x < LEFT_WALL + BALL_RADIUS) {
        // reflect across y axis
        velocity.setXY(velocity.getX() * -1, velocity.getY());

        // then ensure the ball is no longer colliding
        x = LEFT_WALL + BALL_RADIUS;
    } else if (x > RIGHT_WALL - BALL_RADIUS) {
        // reflect across y axis
        velocity.setXY(velocity.getX() * -1, velocity.getY());

        // then ensure the ball is no longer colliding
        x = RIGHT_WALL - BALL_RADIUS;
    } else if (y < BOTTOM_WALL + BALL_RADIUS) {
        // reflect across x axis
        velocity.setXY(velocity.getX(), velocity.getY() * -1);

        // then ensure the ball is no longer colliding
        y = BOTTOM_WALL + BALL_RADIUS;
    } else {
        // then it must be a collision with the top wall
        velocity.setXY(velocity.getX(), velocity.getY() * -1);

        // and lastly ensure that the ball is no longer colliding
        y = TOP_WALL - BALL_RADIUS;
    }

    // change the ball's velocity vector to match what it would be at
    // time of collision
    moveStartTime += elapsedTime * 1000;
    x_0 = x;
    y_0 = y;
    velocity.slow(elapsedTime);
  }

  return hasCollided;
}
