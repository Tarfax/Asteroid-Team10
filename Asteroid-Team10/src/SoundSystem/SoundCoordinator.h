#pragma once

#include <map>
#include <string>
#include <iostream>
#include <SDL_mixer.h>

#define Freq 44100
#define ChunkSize 2048

class SoundCoordinator {

public:
	static void Init();

	static void PlayMusic(std::string id);
	static void LoadMusic(std::string id);

	static void PlayEffect(std::string id);
	static void LoadEffect(std::string id);

	static void Destroy();

private:
	SoundCoordinator();
	static SoundCoordinator* instance;
	static SoundCoordinator* GetInstance() {
		return instance = (instance != nullptr) ? instance : new SoundCoordinator();
	}

	void iPlayEffect(std::string id);
	void iPlayMusic(std::string id);
	void iInit();


	std::map<std::string, Mix_Music*> musicMap;
	std::map<std::string, Mix_Chunk*> effectMap;
	std::map<Mix_Chunk*, int> effectMapChannel;
	int effectsLoaded = 0;
};