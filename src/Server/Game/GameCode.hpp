#ifndef _GAME_CODE_HPP
#define _GAME_CODE_HPP

#include <unordered_set>
#include <cstdlib>

#include "../../utils/AccessMonitor.hpp"


class GameCode {

	static inline AccessMonitor am;

	static inline std::unordered_set<int> codes;
	int code;

	// Search a code not used between 1000 and 9999
	void attributeCode() {
		GameCode::am.lockReader();
		do { this->code = std::rand() % 10000; }
		while ( codes.contains(this->code) or this->code < 1000 );
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
