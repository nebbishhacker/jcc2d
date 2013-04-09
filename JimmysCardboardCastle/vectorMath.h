#pragma once

struct Vector2D
{
	double x, y;

	Vector2D();
	Vector2D(double x_, double y_);

	double length() const;
	double length_squared() const;
	Vector2D normalize() const;

	Vector2D &operator+=(const Vector2D &v2);
	Vector2D &operator-=(const Vector2D &v2);

	Vector2D operator-();

	Vector2D& operator*=(double f);
	Vector2D& operator/=(double f);
};

struct Matrix2x2
{
	double mat[2][2];

	Matrix2x2();
	Matrix2x2(double val);
	Matrix2x2(double val00, double val01, double val10, double val11);
	
	double& operator()(unsigned int x, unsigned int y); // return the double at [x][y]
	double operator()(unsigned int x, unsigned int y) const;

	Matrix2x2& operator*=(Matrix2x2 m);
	Matrix2x2& operator*=(double f);
};

Vector2D operator+(Vector2D v1, const Vector2D &v2);
Vector2D operator-(Vector2D v1, const Vector2D &v2);

Vector2D operator*(Vector2D v, double f);
Vector2D operator*(double f, Vector2D v);
Vector2D operator*(const Matrix2x2 &m, const Vector2D& v);

Vector2D operator/(Vector2D v, double f);

double dot(const Vector2D &v1, const Vector2D &v2);

Matrix2x2 operator*(const Matrix2x2 &m1, const Matrix2x2 &m2);
Matrix2x2 operator*(Matrix2x2 m, double f);
Matrix2x2 operator*(double f, Matrix2x2 m);