#pragma once
#include <Structs/Particle.h>

#include <SDL.h>
#include <vector>
#include <map>

#include <Component/Core/Renderer.h>
#include <Structs/Vector2.h>

#include <FactorySystem/FactoryObject.h>


class ParticleSystem : public Renderer , public FactoryObject {

public:
	static GameObject* GetInstance();

	ParticleSystem(GameObject* gameObject): Renderer(gameObject) { gameObject->name = "ParticleSystem"; }

	void Init() override;
	void OnEnable() override {}
	void Update(float deltaTime) override;
	void OnDraw(SDL_Renderer* renderer) override;
	void OnDisable() override {}
	void Destroy() override;

	void SetData(ObjectData* data) override;

	void SetParticleData(ParticleData data);


private:
	void SetEmissionTime();
	void Emit();

	float time;
	float timer;

	float emissionIntervall;
	bool startOnActivation;

	bool repeat;

	int maxParticles;

	bool isEmitting;
	Sprite* sprite;

	EmitData data;
	//std::map<Sprite, std::vector<Particle>> activeParticles;
	std::vector<Particle*> activeParticles;
	std::vector<Particle*> inactiveParticles;

	
};