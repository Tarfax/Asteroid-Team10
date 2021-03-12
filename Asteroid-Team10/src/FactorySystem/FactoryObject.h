#pragma once

#include <FactorySystem/ObjectDefinitions.h>

class FactoryObject {
protected:
	void SetData(ObjectData* data) {
		definition = data->def;
		OnSetData(data);
	}

	virtual void OnSetData(ObjectData* data) { }

	Predef definition;
};