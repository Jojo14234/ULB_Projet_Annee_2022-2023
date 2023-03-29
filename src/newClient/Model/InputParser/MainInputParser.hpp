#pragma once

#include <vector>
#include <string>

#include "../../../utils/Configs.hpp"
#include "InputParser.hpp"

class MainInputParser : public InputParser {

	QUERY_TYPE query_type = QUERY_TYPE::NONE;

    void createParser() {
        if ( this->size() < 2 ) { return; }
        if ( this->inputs[1] == "normal" )    { this->query_type = QUERY_TYPE::CREATE_GAME; }
        else if ( this->inputs[1] == "fast" ) { this->query_type = QUERY_TYPE::CREATE_GAME; } // todo add query fast
    }

    void messageParser() {
        if ( this->size() < 3 )              { return; }
        if ( this->inputs[1] == "show" )     { this->query_type = QUERY_TYPE::MESSAGE_SHOW; }
        else                                 { this->query_type = QUERY_TYPE::MESSAGE_SEND; }
    }

    void rankingParser() {
        if ( this->size() < 2 )              { return; }
        if ( this->inputs[1] == "pos" )      { this->query_type = QUERY_TYPE::RANKING_POS; }
        else if ( this->inputs[1] == "top" ) { this->query_type = QUERY_TYPE::RANKING_TOP; }
    }

    void friendsParser() {
        if ( this->size() < 2 )                  { return; }
        if ( this->inputs[1] == "list" )         { this->query_type = QUERY_TYPE::FRIENDS_LIST; }
        else if ( this->inputs[1] == "request" ) { this->query_type = QUERY_TYPE::FRIENDS_REQUEST; }
        else if ( this->inputs[1] == "accept" )  { this->query_type = QUERY_TYPE::FRIENDS_ACCEPT; }
        else if ( this->inputs[1] == "refuse" )  { this->query_type = QUERY_TYPE::FRIENDS_REFUSE; }
        else if ( this->inputs[1] == "add" )     { this->query_type = QUERY_TYPE::FRIENDS_ADD; }
        else if ( this->inputs[1] == "remove" )  { this->query_type = QUERY_TYPE::FRIENDS_REMOVE; }
    }

    void joinParser() {
        if ( this->size() < 2 ) { return; }
        if ( this->isValidCode(this->inputs[1]) ) { this->query_type = QUERY_TYPE::JOIN_GAME; }
    }

    bool isValidCode(std::string code) const {
        if  ( code.size() != 4 )    { return false; }
        for ( auto c : code ) { if (not isdigit(c)) return false; }
        return true;
    }

	void parse() override {
		this->split();

		std::string query = this->inputs[0];
		if      ( query == "/create" )  { this->createParser();  }
		else if ( query == "/message" ) { this->messageParser(); }
		else if ( query == "/msg" )     { this->messageParser(); }
		else if ( query == "/rank" )    { this->rankingParser(); }
		else if ( query == "/r")        { this->rankingParser(); }
		else if ( query == "/friends" ) { this->friendsParser(); }
		else if ( query == "/f" )       { this->friendsParser(); }
		else if ( query == "/join" )    { this->joinParser();    }
        else                            { this->query_type = QUERY_TYPE::NONE; }
	}

public:

	MainInputParser(const std::string &input) : InputParser{input} { this->parse(); }

	QUERY_TYPE getQuery() const { return this->query_type; }



};