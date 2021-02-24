#include <SDL.h>
#include<iostream>
#include <stdio.h>

bool Init();
bool LoadMedia();
void Close();

SDL_Window* gWindow{ NULL };
SDL_Surface* gScreenSurface{ NULL };
SDL_Surface* gImage{ NULL };

const int SCREEN_WIDTH{ 640 };
const int SCREEN_HEIGHT{ 480 };

int main(int argc, char* args[]) {

	if (!Init()) {
		printf("Failed to initialize!\n");
	}
	else {
		if (!LoadMedia()) {
			printf("Failed to load media!\n");
		}
		else {

			bool quit{ false };
			SDL_Event e{};

			while (!quit) {

				while (SDL_PollEvent(&e) != 0) {

					if (e.type == SDL_QUIT) {
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN) {

						// switch to allow further implementation of inputs.
						switch (e.key.keysym.sym) {
							
						case SDLK_ESCAPE: 
							quit = true;
							break;
						}
					}
				}

				SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);

				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	Close();
	return 0;
}

bool Init() {

	bool success{ true };

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {

		gWindow = SDL_CreateWindow("Asteroids - by Team 10", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL) {
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {

			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool LoadMedia() {

	bool success{ true };

	gImage = SDL_LoadBMP("CoolImage.bmp");

	if (gImage == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "CoolImage.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void Close() {

	SDL_FreeSurface(gImage);
	gImage = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}