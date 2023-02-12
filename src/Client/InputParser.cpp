#include "InputParser.hpp"


// Private

void InputParser::parse() {
	this->split();	
	const std::string &query = this->input_splited[0];

    if ( query == "/login" ) {
        this-> query_type = QUERY_TYPE::LOGIN;
    }
    else if ( query == "/register" ) {
         this->query_type = QUERY_TYPE::REGISTER;
    }
    else if ( query == "/join" ) {
		this->query_type = QUERY_TYPE::JOIN_GAME;
		// verify code
	}
	else if ( query == "/message" ) {
		this->query_type = QUERY_TYPE::MESSAGE;
		// verify jsp quoi
	}
	else if ( query == "/create" ) { this->query_type = QUERY_TYPE::CREATE_GAME; }
	else if ( query == "/disconnect" ) { this->query_type = QUERY_TYPE::DISCONNECT; }
	else if ( query == "/ranking" ) { this->query_type = QUERY_TYPE::RANKING; }
	else if ( query == "/friends" ) { this->query_type = QUERY_TYPE::FRIENDS; }
	else { this->query_type = QUERY_TYPE::NONE; }
}

void InputParser::split() {
    input_splited.clear();
	std::string str;	
	for ( char e : this->input ) { 
		if ( e == ' ' ) { this->input_splited.push_back(str); str=""; }
		else { str += e; }
	} this->input_splited.push_back(str);
}

const std::string &InputParser::operator[](int n) const {
    return input_splited[n];
}
