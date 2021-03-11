#include "BoxCollider2D.h"
#include "Core/Input.h"
#include "Objects/GameObject.h"
#include <iostream>

bool BoxCollider2D::renderCollider;
std::map<int, BoxCollider2D*> BoxCollider2D::colliders;
int BoxCollider2D::nextId;

BoxCollider2D::BoxCollider2D(GameObject* gameObject)
	: IComponent(gameObject),
	id(nextId++), bounds({0, 0, 0, 0}), layer(lNothing), collideWithlayer(lNothing),
	originalBounds({0, 0, 0, 0})
{
	colliders[id] = this;
}

void BoxCollider2D::Init() {
	transform = gameObject->GetComponent<Transform>();
	//transform = gameObject->GetComponent<Transform>();
}

void BoxCollider2D::Update(float deltaTime) {

	if (Input::GetKeyDown(SDL_SCANCODE_B) == true) {
		renderCollider = !renderCollider;
	}

	std::map<int, BoxCollider2D*>::iterator it;
	for (it = colliders.begin(); it != colliders.end(); it++) {
		if (it->second != this && it->second->IsColliding(this->bounds, collideWithlayer)) {
			int i = it->second->id;
			//std::cout << gameObject->ToString() << " collided with " << it->second->gameObject->ToString() << "\n";
			GameObject::Destroy(gameObject);
		}
	}

	bounds = {(int)transform->X(), (int)transform->Y(), (int)(originalBounds.w * transform->Scale().X), (int)(originalBounds.h * transform->Scale().Y)};
}

void BoxCollider2D::Destroy() {
	colliders.erase(id);
}

void BoxCollider2D::Draw(SDL_Renderer* renderer, Transform* transform) {
	if (renderCollider == true) {
		SDL_SetRenderDrawColor(renderer, 0, 250, 230, 255);
		SDL_RenderDrawRect(renderer, &bounds);
	}
}

void BoxCollider2D::SetBounds(int x, int y, int h, int w) {
	SetBounds(SDL_Rect {x, y, h, w});
}

void BoxCollider2D::SetBounds(SDL_Rect rect) {
	this->originalBounds = rect;
}

void BoxCollider2D::SetLayer(Layer layer) {
	this->layer = layer;
}

void BoxCollider2D::SetCollideWithLayer(Layer layer) {
	this->collideWithlayer = layer;
}

bool BoxCollider2D::IsColliding(SDL_Rect other, Layer collideWithLayer) {
	if (layer != collideWithLayer || collideWithLayer == Layer::lNothing) {
		return false;
	}

	bool isOverlapX = (bounds.x < other.x + other.w) && (bounds.x + bounds.w > other.x);
	bool isOverlapY = (bounds.y < other.y + other.h) && (bounds.y + bounds.h > other.y);

	return isOverlapX && isOverlapY;
}

