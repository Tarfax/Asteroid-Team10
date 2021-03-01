#include "SpriteRenderer.h"
//#include <TextureCoordinator.h>
//#include <iostream>

void SpriteRenderer::Init() { }

void SpriteRenderer::Update(float deltaTime) { }

void  SpriteRenderer::Destroy() {}

void SpriteRenderer::SetSprite(Sprite sprite) {
	this->sprite = sprite;
}

void SpriteRenderer::Draw(SDL_Renderer* renderer, Transform* transform) {
	SDL_Rect rect = {transform->X(), transform->Y(), sprite.Size.X * transform->Scale().X, sprite.Size.Y * transform->Scale().Y};
	SDL_RenderCopyEx(renderer, sprite.Texture, &sprite.GetRect(), &rect, transform->Rotation(), nullptr, SDL_FLIP_NONE);
}

