#include "Music.h"

suken::CMusic::CMusic(){}

suken::CMusic::~CMusic() {}

void suken::CMusic::Load(unsigned char name, const char* fileName) {
	if (music.size() <= name)
		music.resize(name + 1, NULL);
	if (music[name] == NULL) {
		music[name] = LoadSoundMem(fileName);
	}
}

void suken::CMusic::Delete(unsigned char name) {
	if (music.size() > name) {
		if (music[name] != NULL) {
			DeleteSoundMem(music[name]);
			music[name] = NULL;
		}
	}
}

void suken::CMusic::Play(unsigned char name, bool isStop) {
	if (music.size() > name) {
		if (GetCurrentPositionSoundMem(music[name]) != 1) {
			if (PlaySoundMem(music[name], isStop ? DX_PLAYTYPE_NORMAL : DX_PLAYTYPE_BACK) == -1) {
				reTry.push_back(std::make_pair(name, isStop ? DX_PLAYTYPE_NORMAL : DX_PLAYTYPE_BACK));
			}
		}
	}
}

void suken::CMusic::PlayLoop(unsigned char name) {
	if (music.size() > name && CheckSoundMem(music[name]) != 1) {
		if (PlaySoundMem(music[name], DX_PLAYTYPE_LOOP) == -1) {
			reTry.push_back(std::make_pair(name, DX_PLAYTYPE_LOOP));
		}
	}
}

void suken::CMusic::StopLoop(unsigned char name) {
	if (music.size() > name) {
		StopSoundMem(music[name]);
	}
}

void suken::CMusic::ReplayLoop(unsigned char name) {
	if (music.size() > name && CheckSoundMem(music[name]) != 1) {
		PlaySoundMem(music[name], DX_PLAYTYPE_LOOP, FALSE) == -1;
	}
}

void suken::CMusic::ReTry() {
	for (auto i = reTry.begin(); i != reTry.end(); ++i) {
		PlaySoundMem(music[i->first], i->second);
	}
	reTry.clear();
}