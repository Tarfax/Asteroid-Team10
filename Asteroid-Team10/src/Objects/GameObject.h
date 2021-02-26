#pragma once

#include "IObject.h"
#include <iostream>
#include <string>
#include <vector>
#include <Component/SpriteRenderer.h>
//#include <Component/Transform.h>

class GameObject: public IObject {

public:

	virtual void Init();
	virtual void Start() override {}
	virtual void Update(float deltaTime) override;

	virtual void Draw(SDL_Renderer* renderer) override;


	virtual void Destroy() {
		for (IComponent* component : components) {
			component->Destroy();
			delete component;
		}
		components.clear();
	}

public: //Components

	template <typename T, typename = std::enable_if_t<std::is_base_of<IComponent, T>::value>>
	T* AddComponent() {
		T* component = new T(this);

		component->Init();
		components.push_back(component);
		return component;
	}

	template <typename T, typename = std::enable_if_t<std::is_base_of<IComponent, T>::value>>
	T* GetComponent() {
		for (IComponent* component : components) {
			if (typeid(T) == typeid(*component)) {
				return (T*)component;
			}
		}
		return nullptr;
	}



private:
	SpriteRenderer* spriteRenderer;
	Transform* transform;


	std::vector<IComponent*> components;
};