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

	void Close();

private:
	bool LoadMedia(std::string path);
	void HandleInput();
	void Update();
	void Render();

	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Surface* image;

	Input* input;
	GameObject* gameObject;

	Time* time;

	bool isRunning;
};
