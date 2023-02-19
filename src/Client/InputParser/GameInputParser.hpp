#ifndef _GAME_INPUT_PARSER_HPP
#define _GAME_INPUT_PARSER_HPP

#include <vector>
#include <string>

#include "../../utils/Configs.hpp"
#include "InputParser.hpp"


class GameInputParser : public InputParser {

	GAME_QUERY_TYPE query_type = GAME_QUERY_TYPE::NONE;

	// Parse the input from the client
	void parse() override;

public:

	GameInputParser(const std::string &input) : InputParser{input} { this->parse(); }
	
	// GETTERS
	GAME_QUERY_TYPE getQueryType() const { return query_type; }

};

#endif
