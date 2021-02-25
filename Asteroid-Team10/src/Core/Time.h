#pragma once

#include <chrono>

class Time {

public:
	void StartTick();
	void EndTick();
	float GetDeltaTime() const{ return deltaTime; }
private:
	float deltaTime;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::duration<float> difference;
};
