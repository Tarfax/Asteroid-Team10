#pragma once
#include "Component/Behaviour/Behaviour.h"
#include "FactorySystem/FactoryObject.h"

class UFO : public Behaviour, public FactoryObject {

public:
	UFO(GameObject* gameObject) : Behaviour(gameObject) {}

	void Init() override;
	void OnEnable() override {}
	void Update(float deltaTime) override;
	void OnDisable() override {}
	void Destroy() override;

	void OnSetData(ObjectData* data) override;
private:

	Vector2 direction{ 0, 0 };
	float speed{};
	float position{};
	float magnitude{};
	float frequency{};
	float projectileSpeed{};

	void Fire();

	int counter{};
	int framesToNextShot{};
};