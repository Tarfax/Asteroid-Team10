#include "PositionWrapper.h"
#include "Core/Engine.h"
#include <iostream>

void PositionWrapper::Init() {
	this->transform = gameObject->GetComponent<Transform>();
}

void PositionWrapper::Update(float deltaTime) {
	if (transform->Position().X > SCREEN_WIDTH + margin) transform->Position().X = 0 - (texDimensions.X + margin);
	if (transform->Position().X < 0 - (texDimensions.X + margin)) transform->Position().X = SCREEN_WIDTH + margin;

	if (transform->Position().Y > SCREEN_HEIGHT + margin) transform->Position().Y = 0 - (texDimensions.Y + margin);
	if (transform->Position().Y < 0 - (texDimensions.Y + margin)) transform->Position().Y = SCREEN_HEIGHT + margin;

}

void PositionWrapper::Destroy()
{
}

void PositionWrapper::SetTexDimensions(SDL_Rect rect)
{
	texDimensions.X = rect.w;
	texDimensions.Y = rect.h;
	//std::cout << texDimensions.X << " " << texDimensions.Y << '\n';
}
