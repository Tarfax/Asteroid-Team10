#pragma once
#include "Component/Behaviour/Behaviour.h"
#include <list>

class Asteroid : public Behaviour {
public:
	Asteroid(GameObject* gameObject) : Behaviour(gameObject) {}
	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;
	static GameObject* GetInstance();
private:
	Vector2 direction{};
	float speed{};
	float rotationSpeed{};
	std::string textureID{"Assets/Sprites/asteroid_1.png"};

private: // object pool stuff

	static std::list<GameObject*> activeObjecets;
	static std::list<GameObject*> inactiveObjecets;

	GameObject* myGameObject{};

	void AddToPool();

public:

	void SetActive(bool comeUpWithName);
};