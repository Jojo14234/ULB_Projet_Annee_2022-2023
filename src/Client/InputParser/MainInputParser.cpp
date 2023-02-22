#include "MainInputParser.hpp"


// Private

void MainInputParser::parse() {
	InputParser::parse();
	const std::string &query = (*this)[0];
	if ( query == "/login" ) { this-> query_type = QUERY_TYPE::LOGIN; }
	else if ( query == "/register" ) { this->query_type = QUERY_TYPE::REGISTER; }
	else if ( query == "/join" ) { 
		if (this->isValidCode()) { this->query_type = QUERY_TYPE::JOIN_GAME; }
	}
	else if ( query == "/message" or query == "/msg" ) {
		if (this->getNbParameters() != 2) { return; }
		if ( (*this)[1] == "show" ) {
			this->query_type = QUERY_TYPE::MESSAGE_SHOW;	
		} else {
			this->query_type = QUERY_TYPE::MESSAGE_SEND;
		}
	}
	else if ( query == "/create" ) { this->query_type = QUERY_TYPE::CREATE_GAME; }
	else if ( query == "/disconnect" or query == "/d" ) { this->query_type = QUERY_TYPE::DISCONNECT; }
	else if ( query == "/ranking" or query == "/r") {
		if (this->getNbParameters() != 1) { return; }
		else if ((*this)[1] == "top") { this->query_type = QUERY_TYPE::RANKING_TOP; }
		else if ((*this)[1] == "pos") { this->query_type = QUERY_TYPE::RANKING_POS; }
	}
	else if ( query == "/friends" or query == "/f" ) {
		if (this->getNbParameters() < 1) { return; }
		else if ( (*this)[1] == "list" ) { this->query_type = QUERY_TYPE::FRIENDS_LIST; }
		else if ( (*this)[1] == "request" ) { this->query_type = QUERY_TYPE::FRIENDS_REQUEST; }
		else if ( (*this)[1] == "accept" ) { this->query_type = QUERY_TYPE::FRIENDS_ACCEPT; }
		else if ( (*this)[1] == "refuse" ) { this->query_type = QUERY_TYPE::FRIENDS_REFUSE; }
		else if ( (*this)[1] == "add" ) { this->query_type = QUERY_TYPE::FRIENDS_ADD; }
		else if ( (*this)[1] == "remove" ) { this->query_type = QUERY_TYPE::FRIENDS_REMOVE; }
	}
}

bool MainInputParser::isValidCode() {
	std::string code = (*this)[1];
	if (code.size() != 4) { return false; }
	for (auto c : code) { if (not isdigit(c)) return false; }
	return true;
}
