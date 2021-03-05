#pragma once
#include <Structs/Vector2.h>
#include <Structs/Sprite.h>
#include <iostream>

struct EmitData {
	int Amount;

	float MinLifeTime;
	float MaxLifeTime;

	Vector2 MinVelocity;
	Vector2 MaxVelocity;

	Vector2 MinPositionOffset;
	Vector2 MaxPositionOffset;
};

struct ParticleData {
	Sprite	Sprite;
	bool	Repeat;
	float	EmissionIntervall;
	EmitData Data;
};

struct Particle {

	Particle(Vector2 position, Vector2 velocity, float lifeTime, Sprite sprite)
	: position(position), velocity(velocity), lifeTime(lifeTime), sprite(sprite)
	{ 
		std::cout << "Created with vel: " << velocity.ToString() << std::endl;
	}
	Particle(const Particle& other) {
		std::cout << "Copy copy!" << lifeTime << std::endl;
		this->position = other.position;
		this->velocity = other.velocity;
		this->lifeTime = other.lifeTime;
		this->sprite = other.sprite;
	}

	~Particle() { std::cout << "Particle died " << lifeTime << std::endl; }

	void Draw();
	void Update(float deltaTime);
	bool IsDead();

	Vector2 position;
	Vector2 velocity;
	float lifeTime;

	Sprite sprite;

};