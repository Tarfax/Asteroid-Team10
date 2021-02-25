#pragma once

class IComponent {

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Destroy() = 0;

};