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
	float MinSpeed;
	float MaxSpeed;
	float RotationSpeed;
	int Level;
};

struct PlayerData: public ObjectData {
public:
	PlayerData(): ObjectData() { }

	float Speed;
	float RotationSpeed;
	float Acceleration;
	float FireRate;
	float MomentumAcceleration;
};

struct ProjectileData: public ObjectData {
public:
	ProjectileData(): ObjectData() { }

	float Speed;
	float LifeTime;
	float Scale;
};