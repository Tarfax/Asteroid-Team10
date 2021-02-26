#pragma once

class GameObject;

class IComponent {

public:
	IComponent(GameObject* gameObject) : gameObject(gameObject)  {}
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Destroy() = 0;

	GameObject* gameObject;
};