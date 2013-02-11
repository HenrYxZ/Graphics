#include <math.h>
#include <iostream>
#include <vector>

#include "./common.h"
#include "./ball.h"

using namespace std;

vector<Ball> balls;

int currentTime;

struct mouse {
  int x;
  int y;
  bool dragging;
} mouse;

// displays a ball object on the screen
void DisplayBall(Ball toDisplay) {

  switch (toDisplay.color) {
    case WHITE:
      glColor3f(1.0, 1.0, 1.0);
      break;
    case BLACK:
      glColor3f(0.0, 0.0, 0.0);
      break;
    case RED:
      glColor3f(1.0, 0.0, 0.0);
      break;
    case GREEN:
      glColor3f(0.0, 1.0, 0.0);
    case BLUE:
      glColor3f(0.0, 0.0, 1.0);
      break;
    default:
      glColor3f(0.0, 0.0, 0.0);
      break;
  }

  glBegin(GL_POLYGON);
  for(double i = 0; i < 2 * PI; i += PI / 180) {
    glVertex2f(toDisplay.x + cos(i) * BALL_RADIUS,
      toDisplay.y + sin(i) * BALL_RADIUS);
  }

  glEnd();
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

  // display all of the balls
  for (int i = 0; i < balls.size(); ++i) {
    DisplayBall(balls[i]);
  }

  glFlush();
}

void Mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      // only save location if this is the first down in a drag
      if (!mouse.dragging) {
        mouse.dragging = true;
        mouse.x = x;
        mouse.y = y;
      }
    } else if (state == GLUT_UP) {
      if (mouse.dragging) {
        // we are finished with a drag, we now have the cue hit
        mouse.dragging = false;

        // modifies the velocity of the cueball
        int vel_X = ((mouse.x - x)) / 2;
        int vel_Y = (-1 * (mouse.y - y)) / 2;

        if(vel_X < (-1 * MAX_SPEED) )
          vel_X = (-1 * MAX_SPEED);
        if(vel_X >  MAX_SPEED)
          vel_X = MAX_SPEED;

        if(vel_Y < (-1 * MAX_SPEED))
          vel_Y = (-1 * MAX_SPEED);
        if(vel_Y >  MAX_SPEED)
          vel_Y =  MAX_SPEED;

        balls[0].velocity.setXY(vel_X, vel_Y);
        // sets the time that the cueball was hit
        balls[0].setStartTime(glutGet(GLUT_ELAPSED_TIME));
        balls[0].x_0 = balls[0].x;
        balls[0].y_0 = balls[0].y;
        cout << "Cueball hit with " << balls[0].velocity.getX() <<
          " X and " << balls[0].velocity.getY() << " Y\n";
      }
    }
  }
  glutPostRedisplay();
}

// The idle function is called when no window events are fired
// we will use it to compute any possible movements that have happened
// on the screen, and post a redisplay if movement has occured
void Idle() {
  bool redisplayNeeded = false;

  // get the time in milliseconds
  currentTime = glutGet(GLUT_ELAPSED_TIME);

  // first, we're going to move all of the balls if they need to be moved
  for (int i = 0; i < balls.size(); i++) {
    bool ballMoved;

    ballMoved = balls[i].move(currentTime);

    if (ballMoved) {
      redisplayNeeded = true;
      break;
    }
  }

  // next, we need to check for collisions among all pairs of balls
  for (int i = 0; i < balls.size(); i++) {
    // the bounds of these two loops will properly check all pairs once
    // and does not check both (i, j) and (j, i).
    for (int j = i + 1; j < balls.size(); ++j) {
      bool ballCollided;

      ballCollided = balls[i].collide(&balls[j]);

      // I am still unsure if we need to redisplay after both
      // a collision and a move, it may be redundant
      if (ballCollided) {
        redisplayNeeded = true;
        break;
      }
    }
  }

  // Lastly, we will want to check for collisions with a wall for each
  // ball we can technically do this in the first for loop of this function,
  // but I vote that we put it here for readability purposes.
  for (int i = 0; i < balls.size(); i++) {
    bool ballCollided = false;

    ballCollided = balls[i].collideWithWall();

    // I'm still unsure if we need to redisplay here
    if (ballCollided) {
      redisplayNeeded = true;
      break;
    }
  }

  // we only want to post a redisplay if we really need it
  if (redisplayNeeded) {
    glutPostRedisplay();
  }
}

void Init(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(0, 0);

  glutCreateWindow("Billiards");
  glutMouseFunc(Mouse);
  glutDisplayFunc(Display);
  glutIdleFunc(Idle);

  glClearColor(0.0, 1.0, 0.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-200.0, 200.0, -150.0, 150.0);
  glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
  Init(argc, argv);

  // initialize 
  mouse.dragging = false;

  // make a white cue  ball, the cueball will always occupy
  // location 0 of the balls vector
  balls.push_back(Ball(-50, 0, WHITE));

  // make some game balls to be knocked around
  balls.push_back(Ball(50, 25, RED));
  balls.push_back(Ball(50, 0, BLACK));
  balls.push_back(Ball(50, -25, BLUE));

  glutMainLoop();
}
