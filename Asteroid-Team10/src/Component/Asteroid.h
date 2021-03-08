#pragma once
#include "Component/Behaviour/Behaviour.h"
#include <unordered_map>

class Asteroid : public Behaviour {
public:
	Asteroid(GameObject* gameObject) : Behaviour(gameObject) {}

	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

	static GameObject* GetInstance();

private:

	float speed{};
	float rotationSpeed{};
	std::string textureID{"Assets/Sprites/asteroid_1.png"};
	Vector2 direction{};
};