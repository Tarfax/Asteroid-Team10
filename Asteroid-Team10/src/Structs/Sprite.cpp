#include "Sprite.h"
#include <TextureCoordinator.h>

Sprite::Sprite() { }

Sprite::~Sprite() {
	SDL_DestroyTexture(Texture);
}

void Sprite::SetTexture(const std::string textureId) {
	TextureId = textureId;
	Flip = SDL_FLIP_NONE;
	Texture = TextureCoordinator::LoadTexture(TextureId, Size);
	Rect = {0, 0, (int)Size.X, (int)Size.Y};
}


