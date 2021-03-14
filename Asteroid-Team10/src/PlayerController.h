#pragma once

#include "Component/Behaviour/Behaviour.h"
#include "ObjectPool.h"
#include "FactorySystem/FactoryObject.h"
#include "Component/Core/Transform.h"
#include <Objects/GameObject.h>
#include <EventSystem/Event.h>
#include <EventSystem/KeyEvent.h>

class PlayerController: public Behaviour, public FactoryObject {

public:
	PlayerController(GameObject* gameObject): Behaviour(gameObject) { gameObject->name = "Player Controller"; }
	~PlayerController() { 
		std::cout << " player controller detele? " << std::endl;
		//delete playerController; 
	}

	//GameObject* GetInstance();
	static PlayerController* playerController;

protected:
	void OnInit()					 override;
	void OnEnable() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy()				 override;
	void OnCollision(BoxCollider2D* other) override;
	void OnDisable() override;
	void OnSetData(ObjectData* data) override;

private:

	//float IncrementTowards(float currentSpeed, float targetSpeed, float acceleration, float deltaTime);

	void Fire();

	void OnEvent(Event& event);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	void HandleInput(float deltaTime);

	//Transform* transform;

	float maxSpeed;
	float acceleration;
	float accelFalloffStart;
	float rotationSpeed = 100;
	
	Vector2 momentum {0.0f, 0.0f};
	float momentumFalloff;

	float fireRate;
	float fireRateTimer;

	float respawnInvulnerable = 3.0f;
	bool isAlive = false;
};