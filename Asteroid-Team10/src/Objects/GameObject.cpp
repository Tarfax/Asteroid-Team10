#include "GameObject.h"

void GameObject::Init() {
	transform = AddComponent<Transform>();
	spriteRenderer = nullptr;
}

void GameObject::Update(float deltaTime) {
	for (IComponent* c : components) {
		c->Update(deltaTime);
	}
}

void GameObject::Draw(SDL_Renderer* renderer) {
	if (spriteRenderer == nullptr) {
		spriteRenderer = GetComponent<SpriteRenderer>();
	}
	spriteRenderer->Draw(renderer, transform);
}


