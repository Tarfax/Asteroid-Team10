#pragma once

#include <FactorySystem/ObjectDefinitions.h>

class FactoryObject {
protected:
	virtual void SetData(ObjectData* data) { }
};