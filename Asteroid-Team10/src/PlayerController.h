#pragma once

#include "Component/IComponent.h"

class PlayerController: public IComponent {
	
public:
	static PlayerController* Instance() {
		return playerController = (playerController != nullptr) ? playerController : new PlayerController();
	}

	void Init();
	void Update(float deltaTime);
	void Destroy();

private:
	PlayerController() {}
	~PlayerController() { delete playerController; }


	static PlayerController* playerController;


};