#pragma once
#include <random>

#define PI 3.14159265359f
class Mathf {
public:

	inline static float DegToRad(double degree) {
		return (degree * (PI / 180));
	}

	inline static float Lerp(float a, float b, float f) {
		return (a * (1.0f - f)) + (b * f);
	}

	template <typename T>
	inline static int Sign(T val) {
		return (T(0) < val) - (val < T(0));
	}

	inline static float RandomFloat() {
		static std::mt19937 randomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> distribution;
		return (float)distribution(randomEngine) / (float) std::numeric_limits<uint32_t>::max();
	}

};

