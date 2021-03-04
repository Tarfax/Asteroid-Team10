#pragma once

#include <EventSystem/Event.h>
#include <sstream>

class KeyEvent: public Event {
public:
	inline int GetKeyCode() const { return keyCode; }

	EventClassCategory(EventCategoryInput | EventCategoryKeyboard)
protected:
	KeyEvent(int keyCode)
		: keyCode(keyCode) { }

	int keyCode;
};

class KeyPressedEvent: public KeyEvent {
public:
	KeyPressedEvent(int keyCode, int repeatCount)
		: KeyEvent(keyCode), repeatCount(repeatCount) { }

	inline int GetRepeatCount() const { return repeatCount; }
	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
		return ss.str();
	}

	EventClassType(KeyPressed)

private:
	int repeatCount;

};

class KeyReleasedEvent: public KeyEvent {

public:
	KeyReleasedEvent(int keyCode)
		: KeyEvent(keyCode) { }

	//inline int GetRepeatCount() const { return repeatCount; }
	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << keyCode << " is released";
		return ss.str();
	}

	EventClassType(KeyReleased)

private:
	//int repeatCount;

};