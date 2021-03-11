#pragma once
#include <Component/Core/IComponent.h>
#include <Component/Core/Transform.h>
#include <Objects/GameObject.h>

class GameObject;
class Behaviour : public IComponent {

public:
	Behaviour(GameObject* gameObject);
	virtual void Init() = 0;
	virtual void OnEnable() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnDisable() = 0;
	virtual void Destroy() = 0;
protected:
	Transform* transform;
};