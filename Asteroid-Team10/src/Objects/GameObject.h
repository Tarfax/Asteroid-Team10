#pragma once

#include "IObject.h"
#include <string>
#include <vector>
#include <Component/SpriteRenderer.h>
#include <Component/Transform.h>
#include <PlayerController.h>
class GameObject: public IObject {

public:

	virtual void Init();
	virtual void Start() override {}
	virtual void Update(float deltaTime) override;

	virtual void Draw(SDL_Renderer* renderer) override;

	void AddComponent() { }

	virtual void Destroy() {
		delete spriteRenderer;
	}

private:
	std::string textureId = "Assets/Sprites/ship.png";
	SpriteRenderer* spriteRenderer;
	Transform* transform;

	PlayerController* playerController;
};