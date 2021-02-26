#include "SpriteRenderer.h"
#include <TextureCoordinator.h>
#include <iostream>

void SpriteRenderer::Init() { }

void SpriteRenderer::Update(float deltaTime) { }

void SpriteRenderer::Destroy() {
	delete texture;
}

void SpriteRenderer::SetSprite(const std::string textureId) {
	this->textureId = textureId;
	texture = TextureCoordinator::LoadTexture(textureId, textureSize);

}

void SpriteRenderer::Draw(SDL_Renderer* renderer, Transform* transform) {
	SDL_Rect rect = {transform->X(), transform->Y(), textureSize.X * transform->Scale().X, textureSize.Y * transform->Scale().Y};
	SDL_Rect source = {0, 0, 32, 32};

	SDL_RenderCopyEx(renderer, texture, &source, &rect, transform->Rotation(), nullptr, SDL_FLIP_NONE);

}


