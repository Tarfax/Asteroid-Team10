#pragma once
#include "Component/Transform.h"
#include <SDL.h>

class PositionWrapper : public IComponent {
public:
	PositionWrapper(GameObject* gameObject): IComponent(gameObject) {}

	void Init();
	void Update(float deltaTime);
	void Destroy();
	void SetTexDimensions(SDL_Rect rect);

private:
	
	Transform* transform;
	Vector2 texDimensions { 0, 0 };
	float margin{ 5.0f };

};