#pragma once
#include "Core/Input.h"
#include <SDL.h>

class Input {
public:

	static bool GetKeyDown(SDL_Scancode);
	static Input* Init();
	void Listen();

private:

	static Input* instance;

	SDL_Event e{ };

	const Uint8* keyStates;

	//void KeyUp();
	void KeyDown();
};