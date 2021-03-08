#pragma once

#include "Objects/GameObject.h"
#include "ObjectPool.h"
#include <FactorySystem/PredefinedObject.h>

class FactoryObject {
	friend class Factory;
protected:
	virtual void SetData(ObjectData* data) { }
};