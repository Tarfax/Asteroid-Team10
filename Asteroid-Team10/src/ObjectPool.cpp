#include "ObjectPool.h"

ObjectPool* ObjectPool::instance = nullptr;
std::map<PoolType, std::set<GameObject*>> ObjectPool::pools;

GameObject* ObjectPool::FetchObject(PoolType pType) {
	for (GameObject* obj : ObjectPool::pools[pType]) {
		if (!obj->IsActive()) {
			return obj;
		}
	}

	GameObject* obj = CreateObject(pType);
	ObjectPool::pools[pType].emplace(obj);
	return obj;
}

void ObjectPool::SetPoolSize(PoolType pType, const int poolSize) {
	int pSize = ObjectPool::pools[pType].size();

	if (pSize < poolSize) {
		int diff = poolSize - pSize;

		for (int i = 0; i < diff; i++) {
			GameObject* obj = CreateObject(pType);
			//obj->SetActive(false);
			ObjectPool::pools[pType].emplace(obj);
		}
	}
	else if (pSize > poolSize) {
		int diff = pSize - poolSize;

		for (int i = 0; i < diff; i++) {
			std::set<GameObject*>::iterator it = ObjectPool::pools[pType].begin();
			GameObject::Destroy(*it);
			ObjectPool::pools[pType].erase(it); // check if this is Ok.
		}
	}
}

ObjectPool* ObjectPool::GetInstance() {
	if (instance == nullptr) {
		instance = new ObjectPool();
	}
	return instance;
}

void ObjectPool::Init() {
	for (int i = AsteroidLvl1Pool; i != End_DoNotUse; i++) {
		std::set<GameObject*> pool;
		PoolType pType = static_cast<PoolType>(i);
		std::pair<PoolType, std::set<GameObject*>> element(pType, pool);
		ObjectPool::pools.emplace(element);
		SetPoolSize(pType, 10);
	}
}

GameObject* ObjectPool::CreateObject(PoolType pType) {
	switch (pType) {
	case AsteroidLvl1Pool:
		return Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl1);
		break;
	case AsteroidLvl2Pool:
		return Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl2);
		break;
	case AsteroidLvl3Pool:
		return Factory::GetInstance<Asteroid>(Predef::Asteroid_Lvl3);
		break;
	case ProjectilePool:
		return Factory::GetInstance<Projectile>(Predef::Projectile);
		break;
	case End_DoNotUse:
		return nullptr;
		break;
	}
}