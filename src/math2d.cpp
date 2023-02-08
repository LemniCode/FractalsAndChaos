#include "math2d.h"


Vector2 createVector(double a, double b) {
    Vector2 v;
    v.x = a;
    v.y = b;
    return v;
}

Vector2 operator +(Vector2 a, Vector2 b) {
    Vector2 res;
    res.x = a.x+b.x;
    res.y = a.y+b.y;
    return res;
}

Vector2 operator -(Vector2 a, Vector2 b) {
    return a + (-1)*b;
}
Vector2 operator *(Vector2 a, double r) {
    a.x *= r;
    a.y *= r;
    return a;
}

Vector2 operator *(double r, Vector2 b) {
    return b*r;
}

double operator *(Vector2 a, Vector2 b) {
    return a.x*b.x + a.y*b.y;
}

double norm(Vector2 a) {
    return sqrt(a*a);
}

Vector2 operator +(Vector2 a, double b) {
    a.x += b;
    a.y += b;
    return a;
}
Vector2 operator +(double b, Vector2 a) {
    return a + b;
}
Vector2 operator -(Vector2 a, double b) {
    return a + (-1)*b;
}
Vector2 operator -(double b, Vector2 a) {
    return (-1)*a + b;
}

Vector2 operator /(Vector2 a, double b) {
    a.x /= b;
    a.y /= b;
    return a;
}
