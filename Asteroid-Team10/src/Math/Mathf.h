#pragma once
#include <random>
#include <Core/Time.h>
#include <iostream>

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
		if (randomInit == false) {
			randomEngine.seed(std::random_device()());
			randomInit = true;
		}
		//static std::mt19937 randomEngine;
		//static std::uniform_int_distribution<std::mt19937::result_type> distribution;
		float randomValue = (float)distribution(randomEngine) / (float)std::numeric_limits<uint32_t>::max();
		std::cout << randomValue << std::endl;
		return randomValue;
	}

private:
	static bool randomInit;

	static std::mt19937 randomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> distribution;

};

