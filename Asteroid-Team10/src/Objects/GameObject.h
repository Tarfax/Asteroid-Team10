#pragma once

#include "IObject.h"
#include <string>
class GameObject : public IObject {

public:
	std::string setInt = "test";
										
	virtual void Init()					{}
	virtual void Start()				{}
	virtual void Update(float deltaTime){}
										
	virtual void Draw()					{}
										
	virtual void Destroy()				{}

};