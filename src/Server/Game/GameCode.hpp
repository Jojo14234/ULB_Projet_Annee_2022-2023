#ifndef _GAME_CODE_HPP
#define _GAME_CODE_HPP

#include <unordered_set>
#include <cstdlib>


class GameCode {

	// maybe add mutex here

	static std::unordered_set<int> codes;
	int code;

	// Search a code not used between 1000 and 9999
	void attributeCode() {
		do { this->code = std::rand() % 10000; }
		while ( codes.contains(this->code) or this->code < 1000 )
	}

public:

	GameCode() { this->attributeCode(); }
	~GameCode() { codes.erase(code); }

	int getCode() const { return code; }

};

#endif
