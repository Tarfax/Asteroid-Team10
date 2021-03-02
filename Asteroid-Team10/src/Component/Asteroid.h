#pragma once
#include "Component/Behaviour/Behaviour.h"

class Asteroid : public Behaviour {
public:
	Asteroid(GameObject* gameObject) : Behaviour(gameObject) {}
	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;
	static GameObject* CreateInstance();
private:
	Vector2 direction{};
	float speed{};
	float rotationSpeed{};
	std::string textureID{"Assets/Sprites/asteroid_1.png"};
};