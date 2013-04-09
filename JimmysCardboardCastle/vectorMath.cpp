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


Matrix2x2::Matrix2x2() {
	mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
}
Matrix2x2::Matrix2x2(double val) {
	mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = val;
}
Matrix2x2::Matrix2x2(double val00, double val01, double val10, double val11)
{
	mat[0][0] = val00;
	mat[0][1] = val01;
	mat[1][0] = val10;
	mat[1][1] = val11;
}
double &Matrix2x2::operator()(unsigned int x, unsigned int y) { return mat[x][y]; }
double Matrix2x2::operator()(unsigned int x, unsigned int y) const { return mat[x][y]; }

Matrix2x2& Matrix2x2::operator*=(Matrix2x2 m)
{
	*this = *this * m;
	return *this;
}
Matrix2x2& Matrix2x2::operator*=(double f)
{
	mat[0][0] *= f;
	mat[0][1] *= f;
	mat[1][0] *= f;
	mat[1][1] *= f;
	return *this;
}

Matrix2x2 operator*(const Matrix2x2 &m1, const Matrix2x2 &m2)
{
	return Matrix2x2(
		m1(0, 0) * m2(0, 0) + m1(1, 0) * m2(0, 1),
		m1(0, 1) * m2(0, 0) + m1(1, 1) * m2(0, 1),
		m1(0, 0) * m2(1, 0) + m1(1, 0) * m2(1, 1),
		m1(0, 1) * m2(1, 0) + m1(1, 1) * m2(1, 1)
		);
}
Matrix2x2 operator*(Matrix2x2 m, double f)
{
	m *= f;
	return m;
}
Matrix2x2 operator*(double f, Matrix2x2 m)
{
	return m * f;
}


Vector2D operator+(Vector2D v1, const Vector2D &v2) { v1 += v2; return v1;}
Vector2D operator-(Vector2D v1, const Vector2D &v2) { v1 -= v2; return v1;}

Vector2D operator*(Vector2D v, double f) { v *= f; return v;}
Vector2D operator*(double f, Vector2D v) { v *= f; return v;}
Vector2D operator*(const Matrix2x2 &m, const Vector2D& v)
{
	return Vector2D(
		m(0, 0) * v.x + m(1, 0) * v.y,
		m(0, 1) * v.x + m(1, 1) * v.y
		);
}

Vector2D operator/(Vector2D v, double f) { v /= f; return v;}

double dot(const Vector2D &v1, const Vector2D &v2) { return v1.x*v2.x + v1.y*v2.y; }