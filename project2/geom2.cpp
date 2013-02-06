#include "./geom2.h"

int distance(int xA, int yA, int xB, int yB) {
  return sqrt(pow((xB - xA), 2) + pow((yB - yA), 2));
}
