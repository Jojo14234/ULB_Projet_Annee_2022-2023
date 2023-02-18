#include "InputParser.hpp"


// Private

void InputParser::parse() {
	this->split();	
	const std::string &query = this->input_splited[0];
    if ( query == "/login" ) { this-> query_type = QUERY_TYPE::LOGIN; }
    else if ( query == "/register" ) { this->query_type = QUERY_TYPE::REGISTER; }
    else if ( query == "/join" ) { 
		if (this->isValidCode()) { this->query_type = QUERY_TYPE::JOIN_GAME; }
		else { this->query_type = QUERY_TYPE::NONE; }
	}
	else if ( query == "/message" ) {
		this->query_type = QUERY_TYPE::MESSAGE;
		// TODO verify something
	}
	else if ( query == "/create" ) { this->query_type = QUERY_TYPE::CREATE_GAME; }
	else if ( query == "/disconnect" ) { this->query_type = QUERY_TYPE::DISCONNECT; }
	else if ( query == "/ranking" ) {
		if (this->getNbParameters() != 1) { this->query_type = QUERY_TYPE::NONE; }
		else if (this->input_splited[1] == "top") { this->query_type = QUERY_TYPE::RANKING_TOP; }
		else if (this->input_splited[1] == "pos") { this->query_type = QUERY_TYPE::RANKING_POS; }
		else { this->query_type = QUERY_TYPE::NONE; }
	}
	else if ( query == "/friends" ) {
		if (this->getNbParameters() != 1) { this->query_type = QUERY_TYPE::NONE; }
		else if ( this->input_splited[1] == "show" ) { this->query_type = QUERY_TYPE::FRIENDS_SHOW; }
		else if ( this->input_splited[1] == "request" ) { this->query_type = QUERY_TYPE::FRIENDS_REQUEST; }
		else if ( this->input_splited[1] == "accept" ) { this->query_type = QUERY_TYPE::FRIENDS_ACCEPT; }
		else if ( this->input_splited[1] == "refuse" ) { this->query_type = QUERY_TYPE::FRIENDS_REFUSE; }
		else if ( this->input_splited[1] == "add" ) { this->query_type = QUERY_TYPE::FRIENDS_ADD; }
		else if ( this->input_splited[1] == "remove" ) { this->query_type = QUERY_TYPE::FRIENDS_REMOVE; }
		else { this->query_type = QUERY_TYPE::NONE; }
	}
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
    return this->input_splited[n];
}

bool InputParser::isValidCode() {
	std::string code = this->input_splited[1];
	if (code.size() != 4) { return false; }
	for (auto c : code) { if (not isdigit(c)) return false; }
	return true;
}
