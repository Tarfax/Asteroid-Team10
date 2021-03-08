#pragma once

#include <vector>
#include <string>
#include <FactorySystem/Predef.h>

struct ObjectData {
public:
	ObjectData() { }
	virtual ~ObjectData() {}
	std::vector<std::string> TextureIds;
	Predef def;
};

struct AsteroidData: public ObjectData {
public:
	AsteroidData() { }

	float Scale;
	float Speed;
	float RotationSpeed;
};

struct PlayerData: public ObjectData {
public:
	PlayerData(): ObjectData() { }

	float Speed;
	float RotationSpeed;
};

struct ProjectileData: public ObjectData {
public:
	ProjectileData(): ObjectData() { }

	float Speed;
	float LifeTime;
	float Scale;
};