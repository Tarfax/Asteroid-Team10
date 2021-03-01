#include "Sprite.h"
#include <TextureCoordinator.h>
#include <iostream>

Sprite::Sprite() { }

void Sprite::SetTexture(const std::string textureId) {
	TextureId = textureId;
	Flip = SDL_FLIP_NONE;
	Texture = TextureCoordinator::LoadTexture(TextureId, Size);

	Rect = {0, 0, (int)Size.X, (int)Size.Y};

}

void Sprite::Destroy() {
	SDL_DestroyTexture(Texture);
	Texture = nullptr;
}


