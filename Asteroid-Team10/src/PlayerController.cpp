#include "PlayerController.h"
#include "Core/Input.h"
#include <SDL.h>
#include <Math/Mathf.h>

PlayerController* PlayerController::playerController = nullptr;

void PlayerController::Init() {
	targetSpeed = speed;
	acceleration = 100.0f;
	rotationSpeed = 100.0f;
}

void PlayerController::Update(float deltaTime) {
	targetSpeed = 0.0f;
	//useMomentum = true;

	if (Input::GetKeyDown(SDL_SCANCODE_A)) {
		transform->Rotation() -= rotationSpeed * deltaTime;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_D)) {
		transform->Rotation() += rotationSpeed * deltaTime;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_W)) {
		targetSpeed = speed;
		/*useMomentum = false;*/

		momentum.X = IncrementTowards(momentum.X, transform->forward.X, 1, deltaTime);
		momentum.Y = IncrementTowards(momentum.Y, transform->forward.Y, 1, deltaTime);
	}

	if (Input::GetKeyDown(SDL_SCANCODE_S)) {
		targetSpeed = -speed;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_H)) {
		transform->Scale().X -= 1 * deltaTime;
	}

	currentSpeed = IncrementTowards(currentSpeed, targetSpeed, acceleration, deltaTime);

	//if (useMomentum == true) {
		transform->Translate(Vector2((currentSpeed * deltaTime) * momentum.X, (currentSpeed * deltaTime) * momentum.Y));

	//}
	//else {
		//transform->Translate(Vector2((currentSpeed * deltaTime) * transform->forward.X, (currentSpeed * deltaTime) * transform->forward.Y));
	//}
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

