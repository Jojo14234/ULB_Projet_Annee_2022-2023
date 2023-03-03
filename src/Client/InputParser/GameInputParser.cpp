#include "GameInputParser.hpp"

void GameInputParser::parse() {
	InputParser::parse();
	const std::string &query = (*this)[0];

	if ( query == "/roll" ) { this->query_type = GAME_QUERY_TYPE::ROLL_DICE; }

    else if (query == "/bid") {
        if (this->getNbParameters() != 1) { std::cout << "Le format de la requète doit être /bid [montant]" << std::endl; return; }
        this->query_type = GAME_QUERY_TYPE::BID;
    }
    else if (query == "/out") {
        this->query_type = GAME_QUERY_TYPE::LEAVE_BID;
    }
	else if ( query == "/arg1" ) {
		if (this->getNbParameters() != 1) { std::cout << this->getNbParameters() << std::endl; return; }
		this->query_type = GAME_QUERY_TYPE::ARG1;
        std::cout << "hllooo" << std::endl;
	}
	else if ( query == "/arg2" ) {
		if (this->getNbParameters() != 2) { return; }
		this->query_type = GAME_QUERY_TYPE::ARG2;
	}
    else if ( query == "/start") {this->query_type = GAME_QUERY_TYPE::START;} // starts game
    else if ( query == "/end") {this->query_type = GAME_QUERY_TYPE::END_TURN;}
    else if (query == "/leave"){
        this->query_type = GAME_QUERY_TYPE::LEAVE;
    }
	else if ( query == "/buy" ) {
		this->query_type = GAME_QUERY_TYPE::BUY;
	}

	else if ( query == "/disconnect" ) { this->query_type = GAME_QUERY_TYPE::LEAVE; }

}
