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
	emitData.MaxLifeTime = 1;

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

	maxParticles = 1000;

	activeParticles.reserve(maxParticles);
	inactiveParticles.reserve(maxParticles);
}

void ParticleSystem::Destroy() {

}

void ParticleSystem::Update(float deltaTime) {
	if (isEmitting == true) {
				Timer timer;
		for (int i = 0; i < activeParticles.size(); i++) {
			activeParticles[i]->Update(deltaTime);

			if (activeParticles[i]->IsDead() == true) {

				delete activeParticles[i];

				activeParticles.erase(activeParticles.begin() + i);
				//std::cout << "Erased particle " << i << " size: " << activeParticles.size() << std::endl;

			}

		}

		if (activeParticles.empty() == true) {
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
	//Timer timer;

	Vector2 thisPosition = gameObject->GetComponent<Transform>()->Position();

	Vector2 position;
	Vector2 velocity;
	float lifeTime;
	//Sprite sprite = sprite;

	for (int i = 0; i < data.Amount; i++) {
		if (activeParticles.size() >= maxParticles) {
			break;
		}

		position.X = thisPosition.X + (Mathf::RandomFloat(data.MinPositionOffset.X, data.MaxPositionOffset.X));
		position.Y = thisPosition.Y + (Mathf::RandomFloat(data.MinPositionOffset.Y, data.MaxPositionOffset.Y));

		velocity.X = Mathf::RandomFloat(data.MinVelocity.X, data.MaxVelocity.X);
		velocity.Y = Mathf::RandomFloat(data.MinVelocity.Y, data.MaxVelocity.Y);

		float lifeTime = Mathf::RandomFloat(data.MinLifeTime, data.MaxLifeTime);

		Particle* particle = new Particle(position, velocity, lifeTime);

		//activeParticles.emplace_back(position, velocity, lifeTime);
		activeParticles.push_back(particle);
	}
	std::cout << "Created particles " << activeParticles.size() << std::endl;
	isEmitting = true;
}

void ParticleSystem::SetParticleData(ParticleData data) {
	this->data = data.Data;
	emissionIntervall = data.EmissionIntervall;
	repeat = data.Repeat;
	//sprite = data.Sprite;

	SetEmissionTime();

	//Emit();
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
			//std::cout <<"position for " << i << " " << p.position.ToString() << std::endl;
			SDL_RenderCopyEx(renderer, sprite.Texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}
