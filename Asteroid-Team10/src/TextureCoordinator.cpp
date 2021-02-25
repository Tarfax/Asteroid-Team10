#include "TextureCoordinator.h"
#include <stdio.h>
#include <SDL_image.h>

TextureCoordinator* TextureCoordinator::intance = nullptr;

void TextureCoordinator::Init(SDL_Renderer* renderer) {
	GetInstance()->renderer = renderer;
}

SDL_Texture* TextureCoordinator::LoadTexture(std::string textureId, Vector2& sizeOut) {

	SDL_Surface* surface = IMG_Load(textureId.c_str());
	if (surface == nullptr) {
		printf("ERROR: TextureCoordinator::LoadTexture - surface: %s", SDL_GetError());
	}

	sizeOut.X = surface->w;
	sizeOut.Y = surface->h;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GetInstance()->renderer, surface);

	if (texture == nullptr) {
		printf("ERROR: TextureCoordinator::LoadTexture - texture: %s", SDL_GetError());
	}

	return texture;
}
