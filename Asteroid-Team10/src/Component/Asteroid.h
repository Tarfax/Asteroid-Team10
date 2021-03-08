#pragma once
#include "Component/Behaviour/Behaviour.h"
#include <unordered_map>
#include <FactorySystem/FactoryObject.h>

class Asteroid : public Behaviour, public FactoryObject {
public:
	Asteroid(GameObject* gameObject) : Behaviour(gameObject) {}

	void Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

	static GameObject* GetInstance();

	void SetData(ObjectData* data) override;
private:

	float speed { };
	float rotationSpeed { };
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
	void SetActive(bool activeState);
};