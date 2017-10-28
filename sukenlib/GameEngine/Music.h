#pragma once

#include "../Manager.h"
#include "../Utility/Graph.h"

#include <unordered_map>

namespace suken {
	class CMusic {
	public:
		CMusic();

		~CMusic();

		void Load(unsigned char name,const char* fileName);

		void Delete(unsigned char name);

		void Play(unsigned char name, bool isStop = false);

		void PlayLoop(unsigned char name);

		void StopLoop(unsigned char name);

		void ReplayLoop(unsigned char name);

	private:
		void ReTry();

		std::vector<std::pair<unsigned char,unsigned char>> reTry;
		std::vector<int> music;
		friend class CSystem;
	};
}