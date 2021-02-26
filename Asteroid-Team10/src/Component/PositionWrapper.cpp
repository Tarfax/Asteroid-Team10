#include "PositionWrapper.h"
#include "Core/Engine.h"

void PositionWrapper::Init() {
	this->transform = gameObject->GetComponent<Transform>();
}

void PositionWrapper::Update(float deltaTime) {
	if (transform->Position().X > SCREEN_WIDTH + 5) transform->Position().X = 0 - margin;
	if (transform->Position().X < 0 - margin) transform->Position().X = SCREEN_WIDTH + 5;

	if (transform->Position().Y > SCREEN_HEIGHT + 5) transform->Position().Y = 0 - margin;
	if (transform->Position().Y < 0 - margin) transform->Position().Y = SCREEN_HEIGHT + 5;

}