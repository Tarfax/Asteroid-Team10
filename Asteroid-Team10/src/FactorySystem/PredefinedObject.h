#pragma once
#include <Structs/Sprite.h>
#include <vector>
#include <Component/Core/IComponent.h>
#include <Objects/GameObject.h>
#include <TextureCoordinator.h>

enum class Predef {
	Player,
	Projectile,
	Asteroid_Lvl1,
	Asteroid_Lvl2,
	Asteroid_Lvl3,
};

class ObjectData {
public:
	ObjectData() {}
	std::vector<std::string> TextureIds;
	Predef def;
};

class AsteroidData: public ObjectData {
public:
	AsteroidData() {}

	float Speed;
	float RotationSpeed;
};

class PlayerData: public ObjectData {
public:
	PlayerData() : ObjectData() {}

	float Speed;
	float RotationSpeed;
};


class PredefinedObject {
public:
	static void AddPredefData(Predef def, ObjectData* data) {
		predefData[def] = data;
	}

	static ObjectData* GetPredef(Predef def) {
		return predefData[def];
	}

	static void Init() {
		pdAsteroid1();
		pdPlayer();
	}

	PredefinedObject() { }

private:
	static void pdAsteroid1() {
		Predef pre = Predef::Asteroid_Lvl1;
		AsteroidData* data = new AsteroidData();
		data->TextureIds.push_back("Assets/Sprites/asteroid_1.png");
		data->RotationSpeed = 50.0f;
		data->Speed = 40.0f;
		data->def = pre;

		AddPredefData(pre, data);
	}

	static void pdPlayer() {
		Predef pre = Predef::Player;
		AsteroidData* data = new AsteroidData();
		data->TextureIds.push_back("Assets/Sprites/ship.png");
		data->RotationSpeed = 140.0f;
		data->Speed = 250.0f;
		data->def = pre;

		AddPredefData(pre, data);
	}

	static std::map<Predef, ObjectData*> predefData;


};

