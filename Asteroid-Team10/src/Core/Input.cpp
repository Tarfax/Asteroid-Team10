#include "Core/Input.h"
#include <string>

Input* Input::instance = nullptr;

Input* Input::Init() {
	instance = (instance != nullptr) ? instance : new Input();
	instance->keyStates = SDL_GetKeyboardState(nullptr);
	instance->hasQuitBeenCalled = false;
	return instance;
}

void Input::Listen()
{
	while (SDL_PollEvent(&e) == true) {
		// switch to allow further implementation of inputs.
		switch (e.type) {

			case SDL_KEYDOWN:
				KeyDown();
				break;
			case SDL_KEYUP:
				KeyUp();
				break;
			case SDL_QUIT:
				hasQuitBeenCalled = true;
				std::cout << "Don't you fucking quit on me!!\n";
				break;
		}

	}

	DispatchEvents();
}


void Input::Reset() {
	std::unordered_map<SDL_Scancode, bool>::iterator it;
	for (it = wasKeyUp.begin(); it != wasKeyUp.end(); it++) {
		wasKeyUp[it->first] = false;
	}
}

void Input::DispatchEvents() {
	//Callback system?
}

bool Input::GetKeyDown(SDL_Scancode key) {
	if (instance->keyStates[key] == 1) {
		if (instance->keyStatesLastFrame[key] > 0) {
			instance->keyStatesLastFrame[key]++;
			return false;
		}
		//std::cout << key << " was pressed" << std::endl;
		instance->keyStatesLastFrame[key]++;
		return true;
	}
	return false;
}

bool Input::GetKeyUp(SDL_Scancode key) {
	if (instance->wasKeyUp.count(key) == 1) {
		return instance->wasKeyUp[key] == true;
	}
	else {
		instance->wasKeyUp[key] = true;
		return true;
	}
	return false;
}

bool Input::GetKey(SDL_Scancode key) {
	return instance->keyStatesLastFrame[key] > 0;
}


void Input::KeyDown() {
	keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyUp() {
	keyStates = SDL_GetKeyboardState(nullptr);

	std::unordered_map<SDL_Scancode, int>::iterator it;
	for (it = keyStatesLastFrame.begin(); it != keyStatesLastFrame.end(); it++) {
		if (keyStates[it->first] == 0 && it->second > 0) {
			//std::cout << it->first << " was released" << std::endl;
			wasKeyUp[it->first] = true;
			it->second = 0;
		}
	}

}
