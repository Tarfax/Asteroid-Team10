#include "SpriteRenderer.h"
#include <TextureCoordinator.h>

void SpriteRenderer::Init() {


}

void SpriteRenderer::Update(float deltaTime) {

}

void SpriteRenderer::Destroy() {
	delete texture;
}

void SpriteRenderer::SetSprite(const std::string textureId) {
	this->textureId = textureId;
	texture = TextureCoordinator::LoadTexture(textureId);
}

void SpriteRenderer::Draw(SDL_Renderer* renderer)
{
	SDL_Rect source = {0, 0, 32, 32};
	SDL_Rect destination = {100, 100, 100, 50};

	SDL_RenderCopyEx(renderer, texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);

}


