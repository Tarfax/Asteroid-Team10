#pragma once
#include "Component/Asteroid.h"
#include <set>

class ObjectPool {
public:
	ObjectPool() {}

	template <typename T, typename = std::enable_if_t<std::is_base_of<Behaviour, T>::value>>
	inline void Init(const int poolSize) {
		for (int i = 0; i < poolSize; i++)
		{
			GameObject* obj = T::GetInstance();
			inactivePool.insert(obj);
		}
	}

	GameObject* GetFromPool();
	void ReturnToPool(GameObject* obj);
	void PrintPools();

private:

	std::set<GameObject*> activePool;
	std::set<GameObject*> inactivePool;
};