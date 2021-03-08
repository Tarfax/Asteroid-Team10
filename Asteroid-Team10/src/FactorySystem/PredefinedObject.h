#pragma once
#include <FactorySystem/ObjectDefinitions.h>
#include <map>
#include <iostream> 
class PredefinedObject {
public:

	static void Init() {
		pdAsteroid1();
		pdAsteroid2();
		pdPlayer();
		pdProjectile();
	}

	static void AddPredefData(Predef def, ObjectData* data) {
		predefData[def] = data;
	}

	static ObjectData* GetPredef(Predef def) {
		return predefData[def];
	}

	
private:
	PredefinedObject();

	static void pdAsteroid1() {
		Predef pre = Predef::Asteroid_Lvl1;
		AsteroidData* data = new AsteroidData();
		data->TextureIds.push_back("Assets/Sprites/asteroid_1.png");
		data->RotationSpeed = 50.0f;
		data->Speed = 40.0f;
		data->def = pre;
		data->Scale = 1.0f;

		AddPredefData(pre, data);
	}

	static void pdAsteroid2() {
		Predef pre = Predef::Asteroid_Lvl1;
		AsteroidData* data = new AsteroidData();
		data->TextureIds.push_back("Assets/Sprites/asteroid_1.png");
		data->RotationSpeed = 50.0f;
		data->Speed = 40.0f;
		data->def = pre;
		data->Scale = 0.66f;

		AddPredefData(pre, data);
	}

	static void pdPlayer() {
		Predef pre = Predef::Player;
		PlayerData* data = new PlayerData();
		data->TextureIds.push_back("Assets/Sprites/ship.png");
		data->RotationSpeed = 140.0f;
		data->Speed = 250.0f;
		data->def = pre;

		AddPredefData(pre, data);
	}

	static void pdProjectile() {
		Predef pre = Predef::Projectile;
		ProjectileData* data = new ProjectileData();
		data->TextureIds.push_back("Assets/Sprites/projectile.png");
		data->Speed = 450.0f;
		data->LifeTime = 0.75f;
		data->def = pre;
		data->Scale = 0.2f;

		AddPredefData(pre, data);
	}

	static std::map<Predef, ObjectData*> predefData;

};

