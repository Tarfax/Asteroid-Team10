#include "TextureCoordinator.h"
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>

TextureCoordinator* TextureCoordinator::instance = nullptr;

void TextureCoordinator::Init(SDL_Renderer* renderer) {
	GetInstance()->renderer = renderer;
}

Sprite* TextureCoordinator::LoadTexture(std::string textureId) {
	/*if (GetInstance()->textures.count(textureId) == 1) {
		sizeOut.X = GetInstance()->textureSize[textureId].X;
		sizeOut.Y = GetInstance()->textureSize[textureId].Y;
		return GetInstance()->textures[textureId];
	}*/

	SDL_Surface* surface = IMG_Load(textureId.c_str());
	if (surface == nullptr) {
		printf("ERROR: TextureCoordinator::LoadTexture - surface: %s", SDL_GetError());
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GetInstance()->renderer, surface);

	if (texture == nullptr) {
		printf("ERROR: TextureCoordinator::LoadTexture - texture: %s", SDL_GetError());
		return nullptr;
	}

	Vector2 size = Vector2(surface->w, surface->h);

	GetInstance()->textures[textureId] = texture;

	Sprite* sprite = new Sprite(texture, size, textureId);

	return sprite;
}

Sprite* TextureCoordinator::GetSpriteFromId(std::string textureId) {

	if (GetInstance()->sprites.count(textureId) == 1) {
		GetInstance()->spritesRefcount[textureId]++;
		return GetInstance()->sprites[textureId];
	}

	Sprite* sprite = LoadTexture(textureId);

	if (sprite == nullptr) {
		printf("ERROR: TextureCoordinator::GetSpriteFromId - sprite is nullptr");
		return nullptr;
	}

	GetInstance()->sprites[textureId] = sprite;
	GetInstance()->spritesRefcount[textureId]++;

	return sprite;
}

void TextureCoordinator::Delete(Sprite* texture) {

	if (GetInstance()->sprites.count(texture->TextureId) == 1) {
		GetInstance()->spritesRefcount[texture->TextureId]--;
		if (GetInstance()->spritesRefcount[texture->TextureId] <= 0) {

			//SDL_DestroyTexture(texture->Texture);

			//GetInstance()->sprites.erase(texture->TextureId);
			//GetInstance()->textures.erase(texture->TextureId);

			//delete texture;
		}
	}

}
