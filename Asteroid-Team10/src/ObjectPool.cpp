#include "ObjectPool.h"

GameObject* ObjectPool::GetFromPool()
{
	if (!inactivePool.empty()) {

		auto it = inactivePool.begin();

		activePool.insert(*it);

		auto r = activePool.find(*it);

		inactivePool.erase(it);

		return *r;
	}
}

void ObjectPool::ReturnToPool(GameObject* obj)
{
	if (activePool.count(obj) == 1) {

		inactivePool.insert(obj);

		activePool.erase(obj);
	}
}

void ObjectPool::PrintPools()
{
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
