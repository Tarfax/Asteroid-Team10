#pragma once
#include "Component/Behaviour/Behaviour.h"
#include <SDL.h>

class PositionWrapper : public Behaviour {
public:
	PositionWrapper(GameObject* gameObject): Behaviour(gameObject) {}

	void Init();
	void OnEnable() override {}
	void Update(float deltaTime);
	void OnDisable() override {}
	void Destroy();
	void SetTexDimensions(SDL_Rect rect);

private:
	Vector2 texDimensions { 0, 0 };
	float margin{ 5.0f };

};