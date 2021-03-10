#pragma once
#include <EventSystem/Event.h>
#include <sstream>
//#include <UI/MainMenu.h>

class MainMenu;

class MenuEvent: public Event {
public:
	MainMenu* mainMenu;

	EventClassCategory(EventCategoryMenu)
protected:
	MenuEvent(MainMenu* mainMenu)
		: mainMenu(mainMenu) { }

};

class MenuStartGameEvent: public MenuEvent {
public:
	MenuStartGameEvent(MainMenu* mainMenu)
		: MenuEvent(mainMenu)
	{ }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "MenuStartGameEvent was pressed";
		return ss.str();
	}

	EventClassType(MenuStartGame)

};

class MenuSettingsEvent: public MenuEvent {
public:
	MenuSettingsEvent(MainMenu* mainMenu)
		: MenuEvent(mainMenu)
	{ }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "MenuSettingsEvent was pressed";
		return ss.str();
	}

	EventClassType(MenuSettings)
};

class MenuCreditsEvent: public MenuEvent {
public:
	MenuCreditsEvent(MainMenu* mainMenu)
		: MenuEvent(mainMenu)
	{ }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "MenuCreditsEvent was pressed";
		return ss.str();
	}

	EventClassType(MenuCredits)
};

class MenuHighScoreEvent: public MenuEvent {
public:
	MenuHighScoreEvent(MainMenu* mainMenu)
		: MenuEvent(mainMenu)
	{ }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "MenuHighScoreEvent was pressed";
		return ss.str();
	}

	EventClassType(MenuHighScore)

};

class MenuQuitGameEvent: public MenuEvent {
public:
	MenuQuitGameEvent(MainMenu* mainMenu)
		: MenuEvent(mainMenu)
	{ }

	std::string ToString() const override {
		std::stringstream ss;
		ss << "MenuQuitGameEvent was pressed";
		return ss.str();
	}

	EventClassType(MenuQuitGame)
};