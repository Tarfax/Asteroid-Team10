#pragma once

#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include <string>

#include "Objects/GameObject.h"
#include "Time.h"
#include "Core/Input.h"

const int SCREEN_WIDTH {640};
const int SCREEN_HEIGHT {480};

class Engine {

public:
	Engine();
	bool Init();

	void Run();

	void Quit();

private:
	void Update();
	void Render();

	std::function<void(int)> InputCallback;

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Surface* image;

	Input* input;
	GameObject* gameObject;
	GameObject* asteroid;
	GameObject* asteroid2;

	Time* time;

	bool isRunning;
};
