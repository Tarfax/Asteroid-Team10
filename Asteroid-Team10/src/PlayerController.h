#pragma once

#include "Component/Core/IComponent.h"
#include "ObjectPool.h"
#include "FactorySystem/FactoryObject.h"
#include "Component/Core/Transform.h"
#include <Objects/GameObject.h>
#include <Action.h>
#include <EventSystem/Event.h>
#include <EventSystem/KeyEvent.h>

class PlayerController: public IComponent, public FactoryObject {

public:
	PlayerController(GameObject* gameObject): IComponent(gameObject) { gameObject->name = "Player Controller"; }
	~PlayerController() { 
		std::cout << " player controller detele? " << std::endl;
		//delete playerController; 
	}

	//GameObject* GetInstance();


	void Init()					 override;
	void OnEnable()				 override {}
	void Update(float deltaTime) override;
	void OnDisable()			 override {}
	void Destroy()				 override;

	void OnSetData(ObjectData* data) override;

	static PlayerController* playerController;
private:

	//float IncrementTowards(float currentSpeed, float targetSpeed, float acceleration, float deltaTime);

	void Fire();

	void OnEvent(Event& event);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	void HandleInput(float deltaTime);

	Transform* transform;

	float maxSpeed;
	float acceleration;
	float accelFalloffStart;
	float rotationSpeed = 100;
	
	Vector2 momentum {0.0f, 0.0f};
	float momentumFalloff;

	float fireRate;
	float fireRateTimer;
};