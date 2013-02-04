#include <math.h>
#include <iostream>
#include <vector>

#include "./common.h"
#include "./ball.h"

using namespace std;

vector<Ball> balls;
Ball cueBall;

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
  for(double i = 0; i < 2 * PI; i += PI / 6) {
    glVertex2f(toDisplay.x + cos(i) * BALL_RADIUS,
      toDisplay.y + sin(i) * BALL_RADIUS);
  }

  glEnd();
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

  DisplayBall(cueBall);

  for (int i = 0; i < balls.size(); i += 1) {
    DisplayBall(balls[i]);
  }

  glFlush();
}

void Mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
    }
  }
  glutPostRedisplay();
}

void Init(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(0, 0);

  glutCreateWindow("Billiards");
  glutMouseFunc(Mouse);
  glutDisplayFunc(Display);

  glClearColor(0.0, 1.0, 0.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-200.0, 200.0, -150.0, 150.0);
  glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
  Init(argc, argv);

  // make a white cue  ball
  cueBall = Ball(-50, 0, WHITE);

  // make some game balls to be knocked around
  balls.push_back(Ball(50, 25, RED));
  balls.push_back(Ball(50, 0, BLACK));
  balls.push_back(Ball(50, -25, BLUE));

  glutMainLoop();
}
