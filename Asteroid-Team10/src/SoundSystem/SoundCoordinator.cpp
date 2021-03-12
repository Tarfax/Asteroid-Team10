#include "SoundCoordinator.h"

SoundCoordinator* SoundCoordinator::instance;

SoundCoordinator::SoundCoordinator() { }

void SoundCoordinator::Init() {
	Create()->iInit();
}

void SoundCoordinator::iInit() {
	Mix_Init(MIX_INIT_MOD | MIX_INIT_OPUS);
	if (Mix_OpenAudio(Freq, MIX_DEFAULT_FORMAT, 2, ChunkSize) < 0) {
		std::cout << Mix_GetError() << std::endl;
	}
}

void SoundCoordinator::PlayMusic(std::string id) {
	Create()->iPlayMusic(id);
}

void SoundCoordinator::iPlayMusic(std::string id) {
	if (Mix_PlayMusic(musicMap[id], -1) == -1) {
		std::cout << Mix_GetError() << ": " << id << std::endl;
	}
}

void SoundCoordinator::LoadMusic(std::string id) {
	Mix_Music* music = Mix_LoadMUS(id.c_str());
	if (music == nullptr) {
		std::cout << Mix_GetError() << ": " << id << std::endl;
		return;
	}
	Create()->musicMap[id] = music;
}

void SoundCoordinator::PlayEffect(std::string id) {
	Create()->iPlayEffect(id);
}

void SoundCoordinator::iPlayEffect(std::string id) {
	if (effectMap.count(id) != 1) {
		LoadEffect(id);
	}
	if (Mix_PlayChannel(effectMapChannel[effectMap[id]], effectMap[id], 0) == -1) {
		std::cout << Mix_GetError() << ": " << id << std::endl;
	}
}

void SoundCoordinator::LoadEffect(std::string id) {
	Mix_Chunk* effect = Mix_LoadWAV(id.c_str());
	if (effect == nullptr) {
		std::cout << Mix_GetError() << ": " << id << std::endl;
		return;
	}
	Create()->effectMap[id] = effect;
	Create()->effectMapChannel[effect] = Create()->effectsLoaded++;
}

void SoundCoordinator::Delete() {

	std::map<std::string, Mix_Music*>::iterator it;
	for (it = Create()->musicMap.begin(); it != Create()->musicMap.end(); it++) {
		Mix_FreeMusic(it->second);
	}

	std::map<std::string, Mix_Chunk*>::iterator it2;
	for (it2 = Create()->effectMap.begin(); it2 != Create()->effectMap.end(); it2++) {
		Mix_FreeChunk(it2->second);
	}

}
