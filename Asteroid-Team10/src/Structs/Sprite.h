#pragma once

#include <string>
#include <SDL.h>
#include <Structs/Vector2.h>

struct Sprite {

public:
	static Sprite* CreateSprite(std::string textureId);

	Sprite(SDL_Texture* texture, Vector2 size, std::string textureId);
	void Destroy();

public:
	const std::string TextureId;
	SDL_Texture* Texture;
	Vector2	Size;
	SDL_RendererFlip Flip;
	SDL_Rect Rect;

};