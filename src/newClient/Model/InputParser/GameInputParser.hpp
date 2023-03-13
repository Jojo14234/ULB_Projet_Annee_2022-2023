/**
 * Project Untitled
 */

#pragma once

#include <vector>
#include <string>

#include "../../../utils/Configs.hpp"
#include "InputParser.hpp"

/*
 * Classe permettant de Parser des inputs durant une partie
 * Hérite de la classe `InputParser`
 *
 * GameInputParser(const string &input)
 */
class GameInputParser : public InputParser {

	GAME_QUERY_TYPE query_type = GAME_QUERY_TYPE::NONE;

	/*
	* This function parses the input string by calling InputParser::parse() function and
	* determines the type of query by examining the first element of the resulting vector.
	* Based on the value of the first element, the function assigns the corresponding value to the `query_type`
	* First element can be :  /arg1, /arg2, /bid, /build, /buy, /disconnect, /end, /exchange, /give-up,
	*                         /leave, /mortgage, /out, /participate, /roll, /select, /sell, /start.
	*/
	void parse() override;

public:

	/*
	 * Constructor of GameInputParser, take a string `Input` as parameters.
	 * It directly split and parse it.
	 */
	GameInputParser(const std::string &input) : InputParser{input} { this->parse(); }
	
	// GETTERS
	GAME_QUERY_TYPE getQueryType() const { return query_type; }

};