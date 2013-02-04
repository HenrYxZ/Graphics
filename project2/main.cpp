#include <math.h>
#include <iostream>
#include "./common.h"

using namespace std;

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);

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
  // DO NOT change the window title.  It is necessary for the screen capture.
  glutCreateWindow("Billiards");
  glutMouseFunc(Mouse);
  glutDisplayFunc(Display);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-200.0, 200.0, -150.0, 150.0);
  glMatrixMode(GL_MODELVIEW);

  glutMainLoop();
}


int main(int argc, char** argv) {
  Init(argc, argv);
}
