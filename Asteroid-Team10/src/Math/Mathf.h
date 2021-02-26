#pragma once


#define PI 3.14159265359f
class Mathf {
public:

	static float DegToRad(double degree) {
		return (degree * (PI / 180));
	}

	inline static float Lerp(float a, float b, float f) {
		return (a * (1.0f - f)) + (b * f);
	}

	template <typename T>
	static int Sign(T val) {
		return (T(0) < val) - (val < T(0));
	}

};

