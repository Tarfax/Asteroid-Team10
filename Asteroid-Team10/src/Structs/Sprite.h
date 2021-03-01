#pragma once

#include <string>
#include <SDL.h>
#include <Structs/Vector2.h>

struct Sprite {

public:
	Sprite();
	void SetTexture(const std::string textureId);

	void Destroy();

	const SDL_Rect& GetRect () { return Rect; }

public:
	std::string      TextureId;
	SDL_Texture* Texture;
	Vector2		     Size;

	SDL_RendererFlip Flip;

	SDL_Rect Rect;

private:
};