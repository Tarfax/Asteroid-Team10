#pragma once
#include "Core/Input.h"
#include <SDL.h>
#include <unordered_map>
#include <PlayerController.h>
#include <EventSystem/Event.h>
#include <EventSystem/KeyEvent.h>

class Input {

public:
	Input() { }

	static bool GetKeyDown(SDL_Scancode);
	static bool GetKeyUp(SDL_Scancode);
	static bool GetKey(SDL_Scancode);

	static Input* Init();
	void Listen();
	void Reset();
	void DispatchEvents();

	bool hasQuitBeenCalled;
private:

	static Input* instance;

	SDL_Event e { };

	const Uint8* keyStates;
	std::unordered_map<SDL_Scancode, int> keyStatesLastFrame;
	std::unordered_map<SDL_Scancode, bool> wasKeyUp;

	void KeyUp();
	void KeyDown();
};
