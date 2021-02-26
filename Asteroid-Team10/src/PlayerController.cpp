#include "PlayerController.h"
#include "Core/Input.h"
#include <SDL.h>

PlayerController* PlayerController::playerController = nullptr;

void PlayerController::Init() {

}

void PlayerController::Update(float deltaTime) {

	if (Input::GetKeyDown(SDL_SCANCODE_A))
		transform->X() -= speed * deltaTime;

	if (Input::GetKeyDown(SDL_SCANCODE_D))
		transform->X() += speed * deltaTime;

	if (Input::GetKeyDown(SDL_SCANCODE_W)) {
		transform->Translate(Vector2((speed * deltaTime) * transform->forward.X, (speed * deltaTime) * transform->forward.Y));
	}

	if (Input::GetKeyDown(SDL_SCANCODE_S))
		transform->Y() += speed * deltaTime;

	if (Input::GetKeyDown(SDL_SCANCODE_E))
		transform->Rotation() += 100 * deltaTime;

	if (Input::GetKeyDown(SDL_SCANCODE_H))
		transform->Scale().X -= 1 * deltaTime;
}




void PlayerController::Destroy() {}

