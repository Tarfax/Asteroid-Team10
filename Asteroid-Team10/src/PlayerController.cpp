#include "PlayerController.h"
#include "Core/Input.h"
#include <SDL.h>
#include <Math/Mathf.h>
#include <Component/PositionWrapper.h>

PlayerController* PlayerController::playerController = nullptr;

GameObject* PlayerController::CreateInstance() {
	GameObject* gameObject = nullptr;

	if (playerController == nullptr) {
		gameObject = new GameObject();
		gameObject->Init();

		playerController = gameObject->AddComponent<PlayerController>();
		SpriteRenderer* spriteRenderer = gameObject->AddComponent<SpriteRenderer>();
		Sprite sprite;
		sprite.SetTexture(playerController->textureId);
		spriteRenderer->SetSprite(sprite);

		PositionWrapper* positionWrapper = gameObject->AddComponent<PositionWrapper>();
		positionWrapper->SetTexDimensions(spriteRenderer->GetRect());

	}
	return gameObject;
}

void PlayerController::Init() {
	targetSpeed = speed;
	acceleration = 100.0f;
	rotationSpeed = 120.0f;
	momentumAcceleration = 1;
	transform = gameObject->GetComponent<Transform>();
}

void PlayerController::Update(float deltaTime) {
	targetSpeed = 0.0f;

	HandleInput(deltaTime);

	currentSpeed = IncrementTowards(currentSpeed, targetSpeed, acceleration, deltaTime);
	transform->Translate(Vector2((currentSpeed * deltaTime) * momentum.X, (currentSpeed * deltaTime) * momentum.Y));

}

void PlayerController::HandleInput(float deltaTime)
{
	if (Input::GetKeyDown(SDL_SCANCODE_A)) {
		transform->Rotation() -= rotationSpeed * deltaTime;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_D)) {
		transform->Rotation() += rotationSpeed * deltaTime;
	}

	if (Input::GetKeyDown(SDL_SCANCODE_W)) {
		targetSpeed = speed;


		if (targetSpeed < 0) {
			momentumAcceleration = 500;
		}
		else {
			momentumAcceleration = 10;
		}

		momentum.X = IncrementTowards(momentum.X, transform->forward.X, momentumAcceleration, deltaTime);
		momentum.Y = IncrementTowards(momentum.Y, transform->forward.Y, momentumAcceleration, deltaTime);
	}

	if (Input::GetKeyDown(SDL_SCANCODE_S)) {
		targetSpeed = -speed;

		if (targetSpeed > 0) {
			momentumAcceleration = 500;
		}
		else {
			momentumAcceleration = 10;
		}

		momentum.X = IncrementTowards(momentum.X, transform->forward.X, momentumAcceleration, deltaTime);
		momentum.Y = IncrementTowards(momentum.Y, transform->forward.Y, momentumAcceleration, deltaTime);
	}

	if (Input::GetKeyDown(SDL_SCANCODE_H)) {
		transform->Scale().X -= 1 * deltaTime;
	}
}


float PlayerController::IncrementTowards(float n, float target, float alpha, float deltaTime) {
	if (n == target) {
		return n;
	}

	float direction = Mathf::Sign(target - n);
	n += alpha * deltaTime * direction;

	return (direction == Mathf::Sign(target - n)) ? n : target;
}

void PlayerController::Destroy() {

}

