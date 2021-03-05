#include "Particle.h"

void Particle::Draw() {
	
}

void Particle::Update(float deltaTime) {
	position += velocity * deltaTime;
	lifeTime -= deltaTime;
}

bool Particle::IsDead() {
	return lifeTime < 0.0f;
}