#pragma once
#include <string>

struct Vector2 {
	float X;
	float Y;

	Vector2(float x, float y) : X(x), Y(y) { }
	Vector2(): X(0.0f), Y(0.0f) { }
	Vector2(float value) : X(value), Y(value) { }
	Vector2(const Vector2* vector): X(vector->X), Y(vector->Y) { }

	std::string ToString() {
		return std::to_string(X) + ", " + std::to_string(Y);
	}
};