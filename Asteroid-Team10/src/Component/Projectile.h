#pragma once

#include "Component/IComponent.h"
#include "Component/Transform.h"
#include "Component/PositionWrapper.h"
#include "Objects/GameObject.h"

class Projectile : public IComponent { 

public:
	static GameObject* GetInstance();

	Projectile(GameObject* gameObject): IComponent(gameObject) { }
	
	~Projectile();
	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

	void SetDirection(Vector2 direction);

private:
	Transform* transform = nullptr;

	Vector2 direction;
	float speed;
	float lifeTime = 3.0f;
	std::string textureId = "Assets/Sprites/projectile.jpg";
};