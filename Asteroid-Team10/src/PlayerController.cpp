#include "PlayerController.h"
#include <SDL.h>

PlayerController* PlayerController::playerController = nullptr;

void PlayerController::Init() { }

void PlayerController::Update(float deltaTime) {
	SDL_Event e { };

	while (SDL_PollEvent(&e) != 0) {


		if (e.type == SDL_KEYDOWN) {

			// switch to allow further implementation of inputs.
			switch (e.key.keysym.sym) {

				case SDLK_a:
					transform->X() -= speed * deltaTime;
					break;
				case SDLK_d:
					transform->X() += speed * deltaTime;
					break;
				case SDLK_w:
					transform->Y() -= speed * deltaTime;
					break;
				case SDLK_s:
					transform->Y() += speed * deltaTime;
				
					break;


				case SDLK_h:
					transform->Scale().X -= 1 * deltaTime;
					break;

				case SDLK_e:
					transform->Rotation() += 1;
					break;
			}
		}
	}
}

void PlayerController::Destroy() {}

