#pragma once

#include "Component/Projectile.h"
#include "Component/Asteroid.h"
#include "FactorySystem/Factory.h"
#include <set>
#include <map>

enum PoolType {
	AsteroidLvl1Pool,
	AsteroidLvl2Pool,
	AsteroidLvl3Pool,
	ProjectilePool,
	End_DoNotUse
};

class FactoryObject;

class ObjectPool {
public:
	ObjectPool() { }

	static void Init();

	static GameObject* FetchObject(PoolType pType);

	static void SetPoolSize(PoolType pType, const int poolSize);

	static ObjectPool* GetInstance();

private:

	static ObjectPool* instance;
	static std::map<PoolType, std::set<GameObject*>> pools;
	//bool poolCanExtend{ false };

	static GameObject* CreateObject(PoolType pType);
};