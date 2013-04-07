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

	Vector2D &operator*=(double f);
	Vector2D &operator/=(double f);
};

Vector2D operator+(Vector2D v1, const Vector2D &v2);
Vector2D operator-(Vector2D v1, const Vector2D &v2);

Vector2D operator*(Vector2D v, double f);
Vector2D operator*(double f, Vector2D v);

Vector2D operator/(Vector2D v, double f);

double dot(const Vector2D &v1, const Vector2D &v2);