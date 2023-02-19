#include "GameInputParser.hpp"

void GameInputParser::parse() {
    InputParser::parse();
    const std::string &query = (*this)[0];

    if ( query == "/roll") { this->query_type = GAME_QUERY_TYPE::ROLL_DICE; }

    

    else if ( query == "/disconnect" ) { this->query_type = GAME_QUERY_TYPE::LEAVE; }

}
