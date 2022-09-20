#include <math.h>
#include <stdio.h>

typedef struct{
  float x;
  float y;
} Point;

float distance(Point *p1, Point *p2) {
  float a = p1->x - p2->x;
  float b = p1->y - p2->y;
  return sqrtf(a*a + b*b);
}

float area(Point *p1, Point *p2, Point *p3) {
  return 0.5 * fabs(p1->x * p2->y - p2->x * p1->y + p2->x * p3->y - p3->x * p2->y + p3->x * p1->y - p1->x * p3->y);
}

int main() {
  Point A = {2.5, 6};
  Point B = {1, 2.2};
  Point C = {10, 6};

  printf("Distance between A and B: %f\n", distance(&A, &B));
  printf("Area of triangle ABC: %f\n", area(&A, &B, &C));

  return 0;
}
