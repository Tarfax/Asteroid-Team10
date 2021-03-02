#include "Core/Input.h"

Input* Input::instance = nullptr;

void Input::Listen()
{
	while (SDL_PollEvent(&e) == true) {
		// switch to allow further implementation of inputs.
		switch (e.type) {

		case SDL_KEYDOWN:
			KeyDown();
			break;
		case SDL_QUIT:
			// quit func
			break;
		}
		
	}
}

bool Input::GetKeyDown(SDL_Scancode key) {
	return instance->keyStates[key] == 1;
}

Input* Input::Init()
{
	instance = (instance != nullptr) ? instance : new Input();
	instance->keyStates = SDL_GetKeyboardState(nullptr);
	return instance;
}

void Input::KeyDown()
{
	keyStates = SDL_GetKeyboardState(nullptr);
}
