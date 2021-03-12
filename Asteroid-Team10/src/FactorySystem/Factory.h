#pragma once

#include <FactorySystem/FactoryObject.h>
#include <ObjectPool.h>
#include "FactorySystem/PredefinedObject.h"

#include <Objects/GameObject.h>
class GameObject;

class Factory {

public:

	template <typename T, typename = std::enable_if_t<std::is_base_of<FactoryObject, T>::value>>
	static GameObject* Create(Predef predef) {

		GameObject* gameObject = ObjectPool::FetchObject(predef);
		T* component = nullptr;

		//Mike version
		if (gameObject == nullptr) {
			gameObject = new GameObject();
			component = gameObject->AddComponent<T>();
		}
		else {
			component = gameObject->GetComponent<T>();
		}

		component->OnSetData(PredefinedObject::GetPredef(predef));
		return gameObject;
	}

	//Mike version
	static bool Destroy(GameObject* gameObject, Predef predef) {
		if (ObjectPool::PoolObject(gameObject, predef) == true) {
			return true;
		}
		return false;
	}

private:

	//Object pool here?

};