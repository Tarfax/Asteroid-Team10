#include "Vector2.h"
#define PI 3.1415f

Vector2& Vector2::Add(const Vector2& vec)
{
	this->X += vec.X;
	this->Y += vec.Y;

	return *this;
}

Vector2& Vector2::Subtract(const Vector2& vec)
{
	this->X -= vec.X;
	this->Y -= vec.Y;

	return *this;
}

Vector2& Vector2::Multiply(const Vector2& vec)
{
	this->X *= vec.X;
	this->Y *= vec.Y;

	return *this;
}

Vector2& Vector2::Divide(const Vector2& vec)
{
	this->X /= vec.X;
	this->Y /= vec.Y;

	return *this;
}

Vector2& Vector2::Normalize()
{
	float length = std::sqrt(X * X + Y * Y);
	X /= length;
	Y /= length;
	return *this;
}

Vector2 Vector2::Normalized() {
	if (X != 0 || Y != 0) {
		float lenght = Length(this);
		return Vector2(
			X / lenght,
			Y / lenght);
	}
	else {
		return Vector2(0, 0);
	}
}

float Vector2::Length(const Vector2& v1)
{
	return sqrt(pow(X, 2) + pow(Y, 2));
}

float Vector2::Distance(const Vector2& v1, const Vector2& v2)
{
	float distance = ((v1.X - v2.X) * (v1.X - v2.X) + (v1.Y - v2.Y) * (v1.Y - v2.Y));
	return distance;
}

float Vector2::Direction(const Vector2& v1, const Vector2& v2) {
	Vector2 diff;

	diff.X = ((v1.X > v2.X) ? v1.X - v2.X : v2.X - v1.X);
	diff.Y = ((v1.Y > v2.Y) ? v1.Y - v2.Y : v2.Y - v1.Y);

	return atan(diff.Y / diff.X) * 180.0f / PI;
}

 float Vector2::DotProduct(const Vector2& v1, const Vector2& v2) {
	return v1.X * v2.X + v1.Y * v2.Y;
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	return this->Add(vec);
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
	return this->Subtract(vec);
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
	return this->Multiply(vec);
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
	return this->Divide(vec);
}

Vector2& operator+(Vector2& v1, const Vector2& v2)
{
	return v1.Add(v2);
}

Vector2& operator-(Vector2& v1, const Vector2& v2)
{
	return v1.Subtract(v2);
}

Vector2& operator*(Vector2& v1, const Vector2& v2)
{
	return v1.Multiply(v2);
}

Vector2& operator/(Vector2& v1, const Vector2& v2)
{
	return v1.Divide(v2);
}