#pragma once
#include "Component/Transform.h"

class PositionWrapper {
public:

	//PositionWrapper(Transform* transform) : transform(transform) { }
	void Init(Transform* transform);
	void Update();

private:
	
	Transform* transform;
	float margin = { 35.0f };
};