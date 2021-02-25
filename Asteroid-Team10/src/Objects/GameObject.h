#pragma once

#include "IObject.h"
#include <string>
#include <vector>
#include <Component/SpriteRenderer.h>

class GameObject: public IObject {

public:

	virtual void Init() {
		spriteRenderer = new SpriteRenderer();
		spriteRenderer->SetSprite(textureId);
	}

	virtual void Start() {}
	virtual void Update(float deltaTime) {}

	virtual void Draw(SDL_Renderer* renderer) {
		spriteRenderer->Draw(renderer);
	}

	void AddComponent() { }

	virtual void Destroy() {
		delete spriteRenderer;
	}

private:
	std::string textureId = "Assets/Sprites/ship.png";

	SpriteRenderer* spriteRenderer;
};