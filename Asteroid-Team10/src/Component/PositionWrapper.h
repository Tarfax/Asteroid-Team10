#pragma once
#include "Component/Transform.h"

class PositionWrapper : public IComponent {
public:
	PositionWrapper(GameObject* gameObject): IComponent(gameObject) {}

	void Init();
	void Update(float deltaTime);
	void Destroy() {}

private:
	
	Transform* transform;
	float margin = { 35.0f };

};