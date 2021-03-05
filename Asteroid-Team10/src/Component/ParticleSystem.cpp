#include "ParticleSystem.h"
#include "Objects/GameObject.h"
#include "Math/Mathf.h"

GameObject* ParticleSystem::GetInstance() {
	GameObject* gameObject = nullptr;

	gameObject = new GameObject();
	gameObject->Init();

	ParticleSystem* ps = gameObject->AddComponent<ParticleSystem>();

	ParticleData particleData;
	particleData.EmissionIntervall = 2;
	particleData.Repeat = false;
	particleData.Sprite.SetTexture("Assets/Sprites/particle.png");

	EmitData emitData;
	emitData.Amount = 20;

	emitData.MinLifeTime = 1;
	emitData.MaxLifeTime = 3;

	emitData.MinVelocity.X = Mathf::RandomFloat(-100, 100);
	emitData.MinVelocity.Y = Mathf::RandomFloat(-100, 100);
	emitData.MaxVelocity.X = Mathf::RandomFloat(-200, 200);
	emitData.MaxVelocity.Y = Mathf::RandomFloat(-200, 200);

	emitData.MinPositionOffset.X = Mathf::RandomFloat(-0.1f, 0.1f);
	emitData.MinPositionOffset.Y = Mathf::RandomFloat(-0.1f, 0.1f);
	emitData.MaxPositionOffset.X = Mathf::RandomFloat(-2, 2);
	emitData.MaxPositionOffset.Y = Mathf::RandomFloat(-2, 2);

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

	particles.reserve(999);
}

void ParticleSystem::Destroy() {

}

void ParticleSystem::Update(float deltaTime) {
	if (isEmitting == true) {
		for (int i = 0; i < particles.size(); i++) {
			particles[i].Update(deltaTime);

			if (particles[i].IsDead() == true) {
				particles.erase(particles.begin() + i);
				std::cout << "Erased particle " << i << " size: " << particles.size() << std::endl;

			}

		}

		if (particles.empty() == true) {
			isEmitting = false;
		}

	}

	/*timer += deltaTime;
	if (timer > time) {
		if (repeat == true) {
			SetEmissionTime();
		}
	}*/
}

void ParticleSystem::Emit() {
	Vector2 thisPosition = gameObject->GetComponent<Transform>()->Position();

	Vector2 position;
	Vector2 velocity;
	float lifeTime;
	//Sprite sprite = sprite;

	for (int i = 0; i < data.Amount; i++) {

		position.X = thisPosition.X + (Mathf::RandomFloat(data.MinPositionOffset.X, data.MaxPositionOffset.X));
		position.Y = thisPosition.Y + (Mathf::RandomFloat(data.MinPositionOffset.Y, data.MaxPositionOffset.Y));

		velocity.X = Mathf::RandomFloat(data.MinVelocity.X, data.MaxVelocity.X);
		velocity.Y = Mathf::RandomFloat(data.MinVelocity.Y, data.MaxVelocity.Y);

		std::cout << "Velocity: " << velocity.ToString() << std::endl;

		float lifeTime = Mathf::RandomFloat(data.MinLifeTime, data.MaxLifeTime);

		particles.emplace_back(position, velocity, lifeTime, sprite);


	}
	std::cout << "Created particles " << particles.size() << std::endl;
	isEmitting = true;
}

void ParticleSystem::SetParticleData(ParticleData data) {
	this->data = data.Data;
	emissionIntervall = data.EmissionIntervall;
	repeat = data.Repeat;
	sprite = data.Sprite;
	SetEmissionTime();

	Emit();
}

void ParticleSystem::SetEmissionTime() {
	time = Mathf::RandomFloat(0, emissionIntervall);
	timer = time;
}

void ParticleSystem::Draw(SDL_Renderer* renderer) {
	if (isEmitting == true) {
		SDL_Rect& source = sprite.Rect;
		SDL_Rect destination;
		for (int i = 0; i < particles.size(); i++) {
			Particle& p = particles[i];
			destination = {(int)p.position.X, (int)p.position.Y, source.w, source.h};
			//std::cout <<"position for " << i << " " << p.position.ToString() << std::endl;
			SDL_RenderCopyEx(renderer, sprite.Texture, &source, &destination, 0, nullptr, SDL_FLIP_NONE);
		}
	}
}
