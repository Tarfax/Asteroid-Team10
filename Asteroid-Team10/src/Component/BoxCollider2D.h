#pragma once

#include "Component/IComponent.h"
#include "Component/Transform.h"
//#include "Structs/Vector2.h"
#include <SDL.h>
#include <map>

class BoxCollider2D : public IComponent {

public:
	BoxCollider2D(GameObject* gameObject);

	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

	void Draw(SDL_Renderer* renderer, Transform* transform);

	void SetBounds(int x, int y, int h, int w);
	void SetBounds(SDL_Rect rect);

	void Set(int x, int y, Vector2 scale);

	bool IsColliding(SDL_Rect testAgainst);

private:
	SDL_Rect bounds;

	int id;
	static int nextId;

	static bool renderCollider;
	static std::map<int, BoxCollider2D*> colliders;
};