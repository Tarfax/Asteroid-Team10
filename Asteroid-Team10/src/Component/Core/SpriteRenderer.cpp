#include "SpriteRenderer.h"
//#include <TextureCoordinator.h>
#include <iostream>

void SpriteRenderer::Init() { }

void SpriteRenderer::Update(float deltaTime) { }

void  SpriteRenderer::Destroy() {
	sprite->Destroy();
}

void SpriteRenderer::SetSprite(Sprite* sprite) {
	this->sprite = sprite;
}

void SpriteRenderer::OnDraw(SDL_Renderer* renderer) {
	SDL_Rect onScreenSize = {transform->X(), transform->Y(), sprite->Size.X * transform->Scale().X, sprite->Size.Y * transform->Scale().Y};
	SDL_RenderCopyEx(renderer, sprite->Texture, &sprite->Rect, &onScreenSize, transform->Rotation(), nullptr, sprite->Flip);
}

SDL_Rect SpriteRenderer::GetRect() {
	return sprite->Rect;
}
