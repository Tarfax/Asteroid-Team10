#include "TextureCoordinator.h"
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>

TextureCoordinator* TextureCoordinator::instance = nullptr;

void TextureCoordinator::Init(SDL_Renderer* renderer) {
	GetInstance()->renderer = renderer;
}

SDL_Texture* TextureCoordinator::LoadTexture(std::string textureId, Vector2& sizeOut) {
	if (GetInstance()->textures.count(textureId) == 1) {
		sizeOut.X = GetInstance()->textureSize[textureId].X;
		sizeOut.Y = GetInstance()->textureSize[textureId].Y;
		return GetInstance()->textures[textureId];
	}

	SDL_Surface* surface = IMG_Load(textureId.c_str());
	if (surface == nullptr) {
		printf("ERROR: TextureCoordinator::LoadTexture - surface: %s", SDL_GetError());
		return nullptr;
	}

	Vector2 size = Vector2(surface->w, surface->h);

	sizeOut.X = size.X;
	sizeOut.Y = size.Y;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GetInstance()->renderer, surface);

	if (texture == nullptr) {
		printf("ERROR: TextureCoordinator::LoadTexture - texture: %s", SDL_GetError());
		return nullptr;
	}

	GetInstance()->textures[textureId] = texture;
	GetInstance()->textureSize[textureId] = size;

	return texture;
}
