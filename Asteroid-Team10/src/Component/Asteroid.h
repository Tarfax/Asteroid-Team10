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

private: // object pool stuff

	static std::unordered_map<int, GameObject*> activeObjects;
	static std::unordered_map<int, GameObject*> inactiveObjects;
	GameObject* myGameObject;
	int myID;

	void AddToPool();
	bool IsActive();

public:

	static GameObject* GetFromPool();
	void SetActive(bool comeUpWithName);
};