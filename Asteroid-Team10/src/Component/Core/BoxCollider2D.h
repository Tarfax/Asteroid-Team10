#pragma once

#include "Component/Core/IComponent.h"
#include "Component/Core/Transform.h"
#include <SDL.h>
#include <map>

enum Layer {
	lNothing = 1 << 0,
	lAsteroid = 1 << 1,
	lPlayer = 1 << 2,
	lProjectile = 1 << 3
};

inline Layer operator|(Layer a, Layer b) {
	return static_cast<Layer>(static_cast<int>(a) | static_cast<int>(b));
}

class BoxCollider2D: public IComponent {

public:
	BoxCollider2D(GameObject* gameObject);

	void Init() override;
	void OnEnable() override;
	void Update(float deltaTime) override;
	void OnDisable() override;
	void Destroy() override;

	void Draw(SDL_Renderer* renderer, Transform* transform);

	void SetBounds(int x, int y, int h, int w);
	void SetBounds(SDL_Rect rect);

	void SetLayer(Layer layer);
	void SetCollideWithLayer(Layer layer);

	inline Vector2 GetOrigin() { return Vector2 {(float)bounds.x + (bounds.w / 2), (float)bounds.y + (bounds.h / 2)}; }

	inline SDL_Rect GetBounds() const { return bounds; }
	inline void ResetBounds() { bounds = {(int)transform->X(), (int)transform->Y(), (int)(originalBounds.w * transform->Scale().X), (int)(originalBounds.h * transform->Scale().Y)}; }

	bool IsColliding(SDL_Rect testAgainst, Layer collideWithLayer);

private:
	Transform* transform;

	SDL_Rect bounds;
	SDL_Rect originalBounds;

	int id;
	static int nextId;

	Layer layer;
	Layer collideWithlayer;

	static bool renderCollider;
	static std::map<int, BoxCollider2D*> colliders;
};