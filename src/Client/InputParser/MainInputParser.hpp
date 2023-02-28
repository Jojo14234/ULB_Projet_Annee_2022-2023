#ifndef _CLIENT_MAIN_INPUT_PARSER_HPP
#define _CLIENT_MAIN_INPUT_PARSER_HPP

#include <vector>
#include <string>

#include "../../utils/Configs.hpp"
#include "InputParser.hpp"


class MainInputParser : public InputParser {

	QUERY_TYPE query_type = QUERY_TYPE::NONE;
	
	// Parse the input from the client
	void parse() override;

	bool isValidCode();

public:

	MainInputParser(const std::string &input) : InputParser{input} { this->parse(); }

	// GETTERS
	QUERY_TYPE getQueryType() const { return query_type; }
	
};

#endif
