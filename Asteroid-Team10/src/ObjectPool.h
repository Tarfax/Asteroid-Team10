#pragma once
#include "Component/Asteroid.h"
#include <set>

template <typename T, typename = std::enable_if_t<std::is_base_of<Behaviour, T>::value>>
class ObjectPool {
public:
	ObjectPool(const int poolSize) { Init(poolSize); }
	ObjectPool(const int poolSize, const bool poolCanExtend) : 
		poolCanExtend(poolCanExtend) { Init(poolSize); }

	inline GameObject* GetFromPool() {
		if (!inactivePool.empty()) {
			auto it = inactivePool.begin();
			activePool.insert(*it);
			auto r = activePool.find(*it);
			inactivePool.erase(it);
			GameObject* go = *r;
			go->SetActive(true);
			return go;
		}
		else if (poolCanExtend) {
			GameObject* obj = T::GetInstance();
			activePool.insert(obj);
			return obj;
		}
	}

	inline void ReturnToPool(GameObject* obj) {
		if (activePool.count(obj) == 1) {
			obj->SetActive(false);
			inactivePool.insert(obj);
			activePool.erase(obj);
		}
	}

	inline void ExtendPool(const int range) {
		for (int i = 0; i < range; i++)
		{
			GameObject* obj = T::GetInstance();
			obj->SetActive(false);
			inactivePool.insert(obj);
		}
	}

	inline void PrintPools() {
		std::cout << "activePool size: " << activePool.size() << '\n';
		for (auto element : activePool) {
			std::cout << element << " ";
		}
		std::cout << '\n';
		std::cout << "inactivePool size: " << inactivePool.size() << '\n';
		for (auto element : inactivePool) {
			std::cout << element << " ";
		}
		std::cout << '\n';
		std::cout << '\n';
	}

private:

	std::set<GameObject*> activePool;
	std::set<GameObject*> inactivePool;
	bool poolCanExtend{ false };

	inline void Init(const int poolSize) {
		ExtendPool(poolSize);
	}
};