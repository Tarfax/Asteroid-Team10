#pragma once

#include "Component/Behaviour/Behaviour.h"
#include "Component/Core/Transform.h"
#include "Component/PositionWrapper.h"
#include "Objects/GameObject.h"
#include "FactorySystem/FactoryObject.h"

class Projectile : public Behaviour, public FactoryObject { 
public:
	Projectile(GameObject* gameObject): Behaviour(gameObject) { gameObject->name = "Projectile"; }
	
	~Projectile();
	void Init() override;
	void OnEnable() override;
	void Update(float deltaTime) override;
	void OnDisable() override;
	void Destroy() override;

	void SetDirection(Vector2 direction);

	void SetData(ObjectData* data) override;

private:
	Vector2 direction;
	float speed;
	float lifeTime;
	float lifeTimeCounter;
};