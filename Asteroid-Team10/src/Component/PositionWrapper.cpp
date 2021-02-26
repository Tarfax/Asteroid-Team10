#include "PositionWrapper.h"
#include "Core/Engine.h"

void PositionWrapper::Init(Transform* transform)
{
	this->transform = transform;
}

void PositionWrapper::Update()
{
	if (transform->Position().X > SCREEN_WIDTH + 5) transform->Position().X = 0 - margin;
	if (transform->Position().X < 0 - margin) transform->Position().X = SCREEN_WIDTH + 5;

	if (transform->Position().Y > SCREEN_HEIGHT + 5) transform->Position().Y = 0 - margin;
	if (transform->Position().Y < 0 - margin) transform->Position().Y = SCREEN_HEIGHT + 5;
}