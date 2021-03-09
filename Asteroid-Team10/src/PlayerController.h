#pragma once

#include "Component/Core/IComponent.h"
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
	void Update(float deltaTime) override;
	void Destroy()				 override;

	void SetData(ObjectData* data) override;

	static PlayerController* playerController;
private:

	float IncrementTowards(float currentSpeed, float targetSpeed, float acceleration, float deltaTime);

	void Fire();

	void OnEvent(Event& event);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	void HandleInput(float deltaTime);

	Transform* transform;

	float speed = 250;
	float targetSpeed;
	float currentSpeed;
	float acceleration = 30;
	float rotationSpeed = 100;

	bool useMomentum;
	float momentumAcceleration;
	Vector2 momentum;

	float fireRate;
	float fireRateTimer;
};

