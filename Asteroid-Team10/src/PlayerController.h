#pragma once

#include "Component/IComponent.h"
#include "Component/Transform.h"

class PlayerController: public IComponent {

public:
	PlayerController() {
		transform = nullptr;
		if (playerController == nullptr) {
			playerController = this;
		}
	}

	static PlayerController* Instance() {
		return playerController = (playerController != nullptr) ? playerController : nullptr;
	}

	inline void SetTransform(Transform* transform) { this->transform = transform; }

	void Init();
	void Update(float deltaTime);
	void Destroy();

private:
	~PlayerController() { delete playerController; }

	Transform* transform;
	static PlayerController* playerController;

	float speed = 250;
};