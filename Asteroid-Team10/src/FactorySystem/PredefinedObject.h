#pragma once
#include <FactorySystem/ObjectDefinitions.h>
#include <map>
#include <iostream> 
class PredefinedObject {
public:

	static void Init() {
		pdAsteroid1();
		pdAsteroid2();
		pdAsteroid3();
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
		data->TextureIds.push_back("Assets/Sprites/asteroid_lvl01_1.png");
		data->RotationSpeed = 50.0f;
		data->MinSpeed = 50.0f;
		data->MaxSpeed = 70.0f;
		data->def = pre;
		data->Scale = 1.0f;
		data->Level = 1;

		AddPredefData(pre, data);
	}

	static void pdAsteroid2() {
		Predef pre = Predef::Asteroid_Lvl2;
		AsteroidData* data = new AsteroidData();
		data->TextureIds.push_back("Assets/Sprites/asteroid_lvl02_1.png");
		data->RotationSpeed = 33.0f;
		data->MinSpeed = 70.0f;
		data->MaxSpeed = 110.0f;
		data->def = pre;
		data->Scale = 1.0f;
		data->Level = 2;

		AddPredefData(pre, data);
	}

	static void pdAsteroid3() {
		Predef pre = Predef::Asteroid_Lvl3;
		AsteroidData* data = new AsteroidData();
		data->TextureIds.push_back("Assets/Sprites/asteroid_lvl03_1.png");
		data->RotationSpeed = 25.0f;
		data->MinSpeed = 70.0f;
		data->MaxSpeed = 140.0f;
		data->def = pre;
		data->Scale = 1.0f;
		data->Level = 3;

		AddPredefData(pre, data);
	}

	static void pdPlayer() {
		Predef pre = Predef::Player;
		PlayerData* data = new PlayerData();
		data->TextureIds.push_back("Assets/Sprites/ship.png");
		data->RotationSpeed = 270.0f;
		data->Speed = 250.0f;
		data->Acceleration = 250.0f;
		data->FireRate = 0.17f;
		data->MomentumAcceleration = 0.4f;
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

