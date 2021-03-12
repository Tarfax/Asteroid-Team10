#include "TextureCoordinator.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

TextureCoordinator* TextureCoordinator::instance = nullptr;

TextureCoordinator::TextureCoordinator() { }

void TextureCoordinator::Init(SDL_Renderer* renderer) {
	TTF_Init();
	Create()->renderer = renderer;
}

Sprite* TextureCoordinator::LoadTexture(std::string textureId) {

	SDL_Surface* surface = IMG_Load(textureId.c_str());
	if (surface == nullptr) {
		printf("ERROR: TextureCoordinator::LoadTexture - surface: %s", SDL_GetError());
		return nullptr;
	}

	Vector2 size = Vector2(surface->w, surface->h);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Create()->renderer, surface);

	if (texture == nullptr) {
		printf("ERROR: TextureCoordinator::LoadTexture - texture: %s", SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(surface);

	Sprite* sprite = new Sprite(texture, size, textureId);
	//Create()->textures[textureId] = texture;

	return sprite;
}

Sprite* TextureCoordinator::GetSpriteFromId(std::string textureId) {

	if (Create()->sprites.count(textureId) == 1) {
		Create()->refcount[Create()->sprites[textureId]]++;
		return Create()->sprites[textureId];
	}

	Sprite* sprite = LoadTexture(textureId);

	if (sprite == nullptr) {
		printf("ERROR: TextureCoordinator::GetSpriteFromId - sprite is nullptr");
		return nullptr;
	}

	Create()->sprites[textureId] = sprite;
	Create()->refcount[sprite]++;

	return sprite;
}

Sprite* TextureCoordinator::GetSpriteFromText(std::string text, std::string fontId, SDL_Color color, int size) {
	int hashCode = HashCode(text, fontId, size, color);
	if (Create()->fonts.count(hashCode) == 1) {
		Create()->refcount[Create()->fonts[hashCode]]++;
		//std::cout << "TextureCoordinator::GetText reuse of "  << fontId << std::endl;

		return Create()->fonts[hashCode];
	}

	TTF_Font* font = TTF_OpenFont(fontId.c_str(), size);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Create()->renderer, surface);

	Sprite* sprite = new Sprite(texture, Vector2(surface->w, surface->h), fontId);
	sprite->IsText = true;
	Create()->fonts[hashCode] = sprite;
	Create()->fontHash[sprite] = hashCode;

	TTF_CloseFont(font);
	SDL_FreeSurface(surface);

	Create()->refcount[sprite]++;

	//std::cout << "TextureCoordinator::GetText creation of " << fontId << std::endl;
	return sprite;
}

void TextureCoordinator::Delete(Sprite* sprite) {

	if (Create()->refcount.count(sprite) == 1) {
		//std::cout << "TextureCoordinator::Delete called on: " << sprite->TextureId << " and count was " << Create()->refcount[sprite] << std::endl;
		Create()->refcount[sprite]--;
	}

}


//Just a simple hash to store this specific text
//I know it can give same result if r g b are switched around. Not an issue for this small game though
int TextureCoordinator::HashCode(const std::string& msg, const std::string& id, int size, SDL_Color color) {
	int hash = 0;

	for (size_t i = 0; i < msg.size(); ++i) {
		hash = hash * 31 + static_cast<int>(msg[i]);
	}

	for (size_t i = 0; i < id.size(); ++i) {
		hash = hash * 31 + static_cast<int>(id[i]);
	}

	hash = hash + size + color.r + color.g + color.b + color.a;
	return hash;
}