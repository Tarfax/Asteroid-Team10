#include "ParticleSystem.h"
#include "Objects/GameObject.h"
#include "Math/Mathf.h"
#include <Utilities/Timer.h>

GameObject* ParticleSystem::GetInstance() {
	GameObject* gameObject = nullptr;

	gameObject = new GameObject();
	gameObject->Init();

	ParticleSystem* ps = gameObject->AddComponent<ParticleSystem>();

	ParticleData particleData;
	particleData.EmissionIntervall = 2;
	particleData.Repeat = true;

	EmitData emitData;
	emitData.Amount = 10000;

	emitData.MinLifeTime = 1;
	emitData.MaxLifeTime = 3;

	emitData.MinVelocity.X = -100;
	emitData.MinVelocity.Y = -100;
	emitData.MaxVelocity.X = 200;
	emitData.MaxVelocity.Y = 200;

	emitData.MinPositionOffset.X = -0.1f;
	emitData.MinPositionOffset.Y = -0.1f;
	emitData.MaxPositionOffset.X = 2;
	emitData.MaxPositionOffset.Y = 2;

	particleData.Data = emitData;

	ps->SetParticleData(particleData);

	SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	spriteRenderer->SetSprite(ps->sprite);

	return gameObject;
}

void ParticleSystem::Init() {
	sprite.SetTexture("Assets/Sprites/particle.png");
	Transform* transform = gameObject->GetComponent<Transform>();
	transform->Translate({150, 150});

	maxParticles = 10000;

	activeParticles.reserve(maxParticles);
	inactiveParticles.reserve(maxParticles);
}

void ParticleSystem::Destroy() {

}

void ParticleSystem::Update(float deltaTime) {
	if (isEmitting == true) {
		Timer timer;

		std::vector<int> deadParticles;

		std::vector<Particle*>::iterator it;
		int counter = 0;
		for (it = activeParticles.begin(); it != activeParticles.end(); ++it) {
			Particle* p = *it;
			p->Update(deltaTime);
			if (p->IsDead() == true) {
				/*if (counter == 0) {
					std::cout << "Time to remove stuff" << std::endl;
				}*/
				inactiveParticles.push_back(p);
				it = activeParticles.erase(activeParticles.begin() + counter);
				if (it == activeParticles.end()) {
					break;
				}
			}
			counter++;
		}

		if (activeParticles.empty() == true) {
			std::cout << "It's empty now" << std::endl;
			isEmitting = false;
		}

	}

	if (/*isEmitting == false && */repeat == true) {
		timer -= deltaTime;
		if (timer < 0.0f) {
			Emit();
			SetEmissionTime();
		}
	}
}

void ParticleSystem::Emit() {
	Vector2 thisPosition = gameObject->GetComponent<Transform>()->Position();

	Vector2 position;
	Vector2 velocity;
	float lifeTime;

	for (int i = 0; i < data.Amount; i++) {
		if (activeParticles.size() >= maxParticles) {
			break;
		}

		position.X = thisPosition.X + (Mathf::RandomFloat(data.MinPositionOffset.X, data.MaxPositionOffset.X));
		position.Y = thisPosition.Y + (Mathf::RandomFloat(data.MinPositionOffset.Y, data.MaxPositionOffset.Y));

		velocity.X = Mathf::RandomFloat(data.MinVelocity.X, data.MaxVelocity.X);
		velocity.Y = Mathf::RandomFloat(data.MinVelocity.Y, data.MaxVelocity.Y);

		float lifeTime = Mathf::RandomFloat(data.MinLifeTime, data.MaxLifeTime);

		Particle* particle;
		if (inactiveParticles.size() > 0) {
			particle = inactiveParticles[0];
			inactiveParticles.erase(inactiveParticles.begin());
			particle->SetData(position, velocity, lifeTime);
		}
		else {
			particle = new Particle(position, velocity, lifeTime);
		}

		activeParticles.push_back(particle);
	}
	isEmitting = true;
}

void ParticleSystem::SetParticleData(ParticleData data) {
	this->data = data.Data;
	emissionIntervall = data.EmissionIntervall;
	repeat = data.Repeat;
	SetEmissionTime();
}

void ParticleSystem::SetEmissionTime() {
	time = Mathf::RandomFloat(0, emissionIntervall);
	timer = time;
}

void ParticleSystem::Draw(SDL_Renderer* renderer) {
	if (isEmitting == true) {
		SDL_Rect& source = sprite.Rect;
		SDL_Rect destination;

		for (int i = 0; i < activeParticles.size(); i++) {
			Particle& p = *activeParticles[i];
			destination = {(int)p.position.X, (int)p.position.Y, source.w, source.h};
			SDL_RenderCopyEx(renderer, sprite.Texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}
