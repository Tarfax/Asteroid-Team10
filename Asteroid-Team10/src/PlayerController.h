#pragma once

#include "Component/Core/IComponent.h"
#include "Component/Core/Transform.h"
#include <Objects/GameObject.h>
#include <Action.h>
#include <EventSystem/Event.h>
#include <EventSystem/KeyEvent.h>

class PlayerController: public IComponent {

public:
	PlayerController(GameObject* gameObject) : IComponent(gameObject) { }
		
	static GameObject* CreateInstance();

	float IncrementTowards(float currentSpeed, float targetSpeed, float acceleration, float deltaTime);

	void Init();
	void Update(float deltaTime);
	void HandleInput(float deltaTime);
	void Fire();
	void Destroy();

private:
	~PlayerController() { delete playerController; }

	void OnEvent(Event& event);
	bool OnKeyPressedEvent(KeyPressedEvent& e);

	std::string textureId = "Assets/Sprites/ship.png";

	Transform* transform;
	static PlayerController* playerController;

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

