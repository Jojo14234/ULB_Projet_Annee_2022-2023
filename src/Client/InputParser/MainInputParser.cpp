#include "MainInputParser.hpp"


// Private

void MainInputParser::parse() {
	InputParser::parse();
	std::cout << "ta grand mere" << std::endl;
	const std::string &query = (*this)[0];
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
		else if ((*this)[1] == "top") { this->query_type = QUERY_TYPE::RANKING_TOP; }
		else if ((*this)[1] == "pos") { this->query_type = QUERY_TYPE::RANKING_POS; }
		else { this->query_type = QUERY_TYPE::NONE; }
	}
	else if ( query == "/friends" ) {
		if (this->getNbParameters() < 1) { this->query_type = QUERY_TYPE::NONE; }
		else if ( (*this)[1] == "show" ) { this->query_type = QUERY_TYPE::FRIENDS_SHOW; }
		else if ( (*this)[1] == "request" ) { this->query_type = QUERY_TYPE::FRIENDS_REQUEST; }
		else if ( (*this)[1] == "accept" ) { this->query_type = QUERY_TYPE::FRIENDS_ACCEPT; }
		else if ( (*this)[1] == "refuse" ) { this->query_type = QUERY_TYPE::FRIENDS_REFUSE; }
		else if ( (*this)[1] == "add" ) { this->query_type = QUERY_TYPE::FRIENDS_ADD; }
		else if ( (*this)[1] == "remove" ) { this->query_type = QUERY_TYPE::FRIENDS_REMOVE; }
		else { this->query_type = QUERY_TYPE::NONE; }
	}
	else { this->query_type = QUERY_TYPE::NONE; }
}

bool MainInputParser::isValidCode() {
	std::string code = (*this)[1];
	if (code.size() != 4) { return false; }
	for (auto c : code) { if (not isdigit(c)) return false; }
	return true;
}
