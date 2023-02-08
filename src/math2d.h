#ifndef MATH2D_H
#define MATH2D_H

#include "math.h"

struct Vector2 {
    double x, y;
};
struct Point {
    int x, y;
};

Vector2 createVector(double a, double b);
Vector2 operator +(Vector2 a, Vector2 b);
Vector2 operator *(Vector2 a, double r);
Vector2 operator -(Vector2 a, Vector2 b);
Vector2 operator *(double r, Vector2 b);
double operator *(Vector2 a, Vector2 b);
Vector2 operator +(Vector2 a, double b);
Vector2 operator +(double b, Vector2 a);
Vector2 operator -(Vector2 a, double b);
Vector2 operator -(double b, Vector2 a);
Vector2 operator /(Vector2 a, double b);

double norm(Vector2 a);



#endif // MATH2D_H
