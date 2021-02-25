#include "SpriteRenderer.h"
#include <TextureCoordinator.h>
#include <iostream>

void SpriteRenderer::Init() {


}

void SpriteRenderer::Update(float deltaTime) {

}

void SpriteRenderer::Destroy() {
	delete texture;
}

void SpriteRenderer::SetSprite(const std::string textureId) {
	this->textureId = textureId;
	texture = TextureCoordinator::LoadTexture(textureId, textureSize);

}

void SpriteRenderer::Draw(SDL_Renderer* renderer, Transform* transform)
{

	//std::cout << "SpriteRenderer::Draw - Size " << textureSize.ToString() << std::endl;
	//std::cout << "SpriteRenderer::Draw - Scale" << transform->Scale().ToString() << std::endl;

	SDL_Rect rect = {transform->X(), transform->Y(), textureSize.X * transform->Scale().X, textureSize.Y * transform->Scale().Y};
	SDL_Rect source = {0, 0, 32, 32};

	SDL_RenderCopyEx(renderer, texture, &source, &rect, 0, nullptr, SDL_FLIP_NONE);

}


