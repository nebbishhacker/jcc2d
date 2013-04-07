#include "vectorMath.h"
#include <cmath>

Vector2D::Vector2D() { x = y = 0; }

Vector2D::Vector2D(double x_, double y_)
{
	x = x_;
	y = y_;
}

double Vector2D::length() const { return sqrt(x*x + y*y); }
double Vector2D::length_squared() const { return x*x + y*y; }
Vector2D Vector2D::normalize() const
{
	double l = this->length();
	return Vector2D(x / l, y / l);
}

Vector2D &Vector2D::operator+=(const Vector2D &v2) { x += v2.x; y += v2.y; return *this; }
Vector2D &Vector2D::operator-=(const Vector2D &v2) { x -= v2.x; y -= v2.y; return *this; }

Vector2D Vector2D::operator-() { return Vector2D(-x, -y); }

Vector2D &Vector2D::operator*=(double f) { x *= f; y *= f; return *this; }
Vector2D &Vector2D::operator/=(double f) { x /= f; y /= f; return *this; }

Vector2D operator+(Vector2D v1, const Vector2D &v2) { v1 += v2; return v1;}
Vector2D operator-(Vector2D v1, const Vector2D &v2) { v1 -= v2; return v1;}

Vector2D operator*(Vector2D v, double f) { v *= f; return v;}
Vector2D operator*(double f, Vector2D v) { v *= f; return v;}

Vector2D operator/(Vector2D v, double f) { v /= f; return v;}

double dot(const Vector2D &v1, const Vector2D &v2) { return v1.x*v2.x + v1.y*v2.y; }