#ifndef _SERVER_GAME_CODE_HPP
#define _SERVER_GAME_CODE_HPP

#include <unordered_set>
#include <cstdlib>
#include <random>


#include "../../../Utils/AccessMonitor.hpp"


class GameCode {

	static inline AccessMonitor am;

	static inline std::unordered_set<int> codes;
	int code;

	// Search a code not used between 1000 and 9999
	void attributeCode() {
		GameCode::am.lockReader();
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1000, 9999);
        this->code = distrib(gen);
		GameCode::am.unlockReader();
	}
	
	// Remove the code from the codes set
	void removeCode() {
		GameCode::am.lockReader();
        codes.erase(this->code);
        GameCode::am.unlockReader();
	}

public:

	GameCode() { this->attributeCode(); }
	~GameCode() { this->removeCode(); }

	// GETTERS
	int getCode() const { return code; }

};

#endif
