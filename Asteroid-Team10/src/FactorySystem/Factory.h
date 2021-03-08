#pragma once

#include "FactoryObject.h"
#include "ObjectPool.h"

class Factory {

public:
	template <typename T, typename = std::enable_if_t<std::is_base_of<FactoryObject, T>::value>>
	static GameObject* GetInstance(Predef type) {
		GameObject* gameObject = nullptr;

		gameObject = new GameObject();

		T* component = gameObject->AddComponent<T>();
		component->SetData(PredefinedObject::GetPredef(type));

		return gameObject;
	}

private:

	//Object pool here?

};