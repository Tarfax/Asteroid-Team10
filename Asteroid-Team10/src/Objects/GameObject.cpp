#include "GameObject.h"

void GameObject::Init() {
	transform = new Transform();
	transform->Init();

	spriteRenderer = new SpriteRenderer();
	spriteRenderer->Init();
	spriteRenderer->SetSprite(textureId);

	playerController = new PlayerController();
	playerController->Init();
	playerController->SetTransform(transform);
}

void GameObject::Update(float deltaTime) {

	//SDL_Rect destination = {100, 100, 100, 50};

	transform->Update(deltaTime);
	playerController->Update(deltaTime);
	spriteRenderer->Update(deltaTime);

}

void GameObject::Draw(SDL_Renderer* renderer) {
	spriteRenderer->Draw(renderer, transform);
}
