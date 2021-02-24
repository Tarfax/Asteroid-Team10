#pragma once

#include <stdio.h>
#include <SDL.h>
#include <iostream>

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
	void Input();
	void Update();
	void Render();
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Surface* image;

	bool isRunning;
};
