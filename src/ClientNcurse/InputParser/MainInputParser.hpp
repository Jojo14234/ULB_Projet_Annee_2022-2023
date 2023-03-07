#ifndef _CLIENT_MAIN_INPUT_PARSER_HPP
#define _CLIENT_MAIN_INPUT_PARSER_HPP

#include <vector>
#include <string>

#include "../../utils/Configs.hpp"
#include "InputParser.hpp"

class MainInputParser : public InputParser {

private:


	QUERY_TYPE query_type = QUERY_TYPE::NONE;
	
	// Parse the input from the client
	void parse() override {
		this->split();
		std::string query = this->input_splited[0];
		if ( query == "/create" ) { this->query_type = QUERY_TYPE::CREATE_GAME; }
		else if ( query == "/message" or query == "/msg" ) {
			if (this->getNbParameters() != 2) { return; }
			if ( (*this)[1] == "show" ) { this->query_type = QUERY_TYPE::MESSAGE_SHOW; }
			else { this->query_type = QUERY_TYPE::MESSAGE_SEND; }
		}
		else if ( query == "/rank" or query == "/r") {
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

public:

	MainInputParser(const std::string &input) : InputParser{input} { this->parse(); }

	// The n parameter from the input_splited
	const std::string &operator[](int n) const { return this->input_splited[n]; }

	// The nb of parameters (does not count the query type ex : /login remy rkb -> 2, not 3)
	int getNbParameters() const { return input_splited.size() - 1; }
	
	// The query type
	QUERY_TYPE getQueryType() const { return this->query_type; }

    bool isValidCode(std::string code) {
	if  (code.size() != 4)    { return false; }
	for (auto c : code) { if (not isdigit(c)) return false; }
	return true;
}

};

#endif
