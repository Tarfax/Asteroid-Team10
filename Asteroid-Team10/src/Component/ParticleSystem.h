#pragma once
#include <Structs/Particle.h>

#include <SDL.h>
#include <vector>
#include <map>

#include <Component/Core/IComponent.h>
#include <Structs/Vector2.h>




class ParticleSystem : public IComponent{

public:
	static GameObject* GetInstance();

	ParticleSystem(GameObject* gameObject): IComponent(gameObject) {}

	void Init() override;
	void Destroy() override;
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer);

	void SetParticleData(ParticleData data);

private:
	void SetEmissionTime();
	void Emit();

	float time;
	float timer;

	float emissionIntervall;

	bool repeat;

	int maxParticles;

	bool isEmitting;
	Sprite* sprite;

	EmitData data;
	//std::map<Sprite, std::vector<Particle>> activeParticles;
	std::vector<Particle*> activeParticles;
	std::vector<Particle*> inactiveParticles;

	
};