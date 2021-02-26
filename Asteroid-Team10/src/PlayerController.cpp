#include "PlayerController.h"
#include <SDL.h>
#include <iostream>

PlayerController* PlayerController::playerController = nullptr;

void PlayerController::Init() { }

void PlayerController::Update(float deltaTime) {
	//std::cout << "Update" << std::endl;
	
	SDL_Event e { };

	while (SDL_PollEvent(&e) != 0) {


		if (e.type == SDL_KEYDOWN) {

			// switch to allow further implementation of inputs.
			switch (e.key.keysym.sym) {

				case SDLK_a:
					std::cout << "A" << std::endl;
					transform->X() -= speed * deltaTime;
					break;
				case SDLK_d:
					std::cout << "D" << std::endl;

					transform->X() += speed * deltaTime;
					break;
				case SDLK_w:
					std::cout << "W" << std::endl;

					transform->Y() -= speed * deltaTime;
					break;
				case SDLK_s:
					std::cout << "S" << std::endl;

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

