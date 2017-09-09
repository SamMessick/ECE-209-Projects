#include <stdio.h>
#include <math.h>
double distance(double x1, double y1, double x2, double y2) {
  double xn = x2 - x1;
  double yn = y2 - y1;
  return sqrt(pow(xn, 2) + pow(yn, 2));
}

int main() {
  printf("%lf\n", distance(0, 0, 0, 1));
  printf("%lf\n", distance(0, 0, 1, 1));
  printf("%lf\n", distance(0, 0, 4, 0));
}
