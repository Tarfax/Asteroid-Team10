#include "PlayerController.h"
#include "Core/Input.h"
#include <SDL.h>
#include <Math/Mathf.h>

PlayerController* PlayerController::playerController = nullptr;

void PlayerController::Init() {
	targetSpeed = speed;
	acceleration = 100.0f;
}

void PlayerController::Update(float deltaTime) {
	targetSpeed = 0.0f;

	if (Input::GetKeyDown(SDL_SCANCODE_A)) {
		transform->Rotation() -= 100 * deltaTime;
	}
	
	if (Input::GetKeyDown(SDL_SCANCODE_D)) {
		transform->Rotation() += 100 * deltaTime;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_W)) {
		targetSpeed = speed;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_S)) {
		targetSpeed = -speed;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_H)) {
		transform->Scale().X -= 1 * deltaTime;
	}

	currentSpeed = IncrementTowards(currentSpeed, targetSpeed, acceleration, deltaTime);
	transform->Translate(Vector2((currentSpeed * deltaTime) * transform->forward.X, (currentSpeed * deltaTime) * transform->forward.Y));
}


float PlayerController::IncrementTowards(float n, float target, float alpha, float deltaTime) {
	if (n == target) {
		return n;
	}

	float direction = Mathf::Sign(target - n);
	n += alpha * deltaTime * direction;

	return (direction == Mathf::Sign(target - n)) ? n : target;
}



void PlayerController::Destroy() {}

