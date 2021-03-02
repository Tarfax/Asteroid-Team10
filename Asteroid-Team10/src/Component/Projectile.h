#pragma once

#include "Component/Behaviour/Behaviour.h"
#include "Component/Core/Transform.h"
#include "Component/PositionWrapper.h"
#include "Objects/GameObject.h"

class Projectile : public Behaviour { 

public:
	static GameObject* GetInstance();

	Projectile(GameObject* gameObject): Behaviour(gameObject) { }
	
	~Projectile();
	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

	void SetDirection(Vector2 direction);

private:
	Vector2 direction;
	float speed;
	float lifeTime = 0.75f;
	std::string textureId = "Assets/Sprites/projectile.png";
};