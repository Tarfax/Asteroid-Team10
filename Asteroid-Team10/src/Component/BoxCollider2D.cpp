#include "BoxCollider2D.h"
#include "Core/Input.h"
#include <iostream>

bool BoxCollider2D::renderCollider;
std::map<int, BoxCollider2D*> BoxCollider2D::colliders;
int BoxCollider2D::nextId;

BoxCollider2D::BoxCollider2D(GameObject* gameObject): IComponent(gameObject) {
	id = nextId++;
	colliders[id] = this;
}

void BoxCollider2D::Init() { }

void BoxCollider2D::Update(float deltaTime) {
	static int colissions = 0;
	if (Input::GetKeyDown(SDL_SCANCODE_B) == true) {
		renderCollider = !renderCollider;
	}

	std::map<int, BoxCollider2D*>::iterator it;
	for (it = colliders.begin(); it != colliders.end(); it++) {
		if (it->second != this && it->second->IsColliding(this->bounds)) {
			colissions++;
			std::cout << "Collided! " << colissions << "\n";
		}
	}
}

void BoxCollider2D::Destroy() {
	colliders.erase(id);
}

void BoxCollider2D::Draw(SDL_Renderer* renderer, Transform* transform) {
	if (renderCollider == true) {
		//SDL_Rect box = {transform->X(), transform->Y(), bounds.w, bounds.h};

		SDL_SetRenderDrawColor(renderer, 0, 250, 230, 255);
		SDL_RenderDrawRect(renderer, &bounds);
	}
}

void BoxCollider2D::SetBounds(int x, int y, int h, int w) {
	SetBounds(SDL_Rect {x, y, h, w});
}

void BoxCollider2D::SetBounds(SDL_Rect rect) {
	this->bounds = rect;
}

void BoxCollider2D::Set(int x, int y, Vector2 scale) {
	bounds = {x, y, (int)(bounds.w * scale.X), (int)(bounds.h * scale.Y)};
}

bool BoxCollider2D::IsColliding(SDL_Rect other) {
	bool isOverlapX = (bounds.x < other.x + other.w) && (bounds.x + bounds.w > other.x);
	bool isOverlapY = (bounds.y < other.y + other.h) && (bounds.y + bounds.h > other.y);

	return isOverlapX && isOverlapY;
}

