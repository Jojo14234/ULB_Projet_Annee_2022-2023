#include "GameInputParser.hpp"

void GameInputParser::parse() {
	InputParser::parse();
	const std::string &query = (*this)[0];

	if ( query == "/roll" ) { this->query_type = GAME_QUERY_TYPE::ROLL_DICE; }

	else if ( query == "/arg1" ) {
		if (this->getNbParameters() != 1) { return; }
		this->query_type = GAME_QUERY_TYPE::ARG1;
	}
	else if ( query == "/arg2" ) {
		if (this->getNbParameters() != 2) { return; }
		this->query_type = GAME_QUERY_TYPE::ARG2;
	}

	else if ( query == "/disconnect" ) { this->query_type = GAME_QUERY_TYPE::LEAVE; }

}
