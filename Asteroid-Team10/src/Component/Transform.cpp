#include "Transform.h"
#include <iostream>
void Transform::Init() {
	scale = Vector2(1);
	//std::cout << "Transform::Init - Scale " + scale.ToString() << std::endl;

	position = {0,0};
	rotation = 0;
}

void Transform::Update(float deltaTime) {
	std::cout << "Transform::Update - Position: " + position.ToString() << std::endl;
}

void Transform::Destroy() { }
