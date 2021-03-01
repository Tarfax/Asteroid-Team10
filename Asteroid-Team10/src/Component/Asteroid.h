#pragma once
#include "Component/IComponent.h"
#include "Component/Transform.h"

class Asteroid : public IComponent {
public:
	Asteroid(GameObject* gameObject) : IComponent(gameObject) {}
	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;
	static GameObject* CreateInstance();
private:
	Transform* transform;
	Vector2 direction{};
	float speed{};
	float rotationSpeed{};
	std::string textureID{"Assets/Sprites/asteroid_1.png"};
};