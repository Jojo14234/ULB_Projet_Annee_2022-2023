#include "MainInputParser.hpp"


// Private
void MainInputParser::parse() {
	InputParser::parse();
	const std::string &query = (*this)[0];
    switch (query) {
        case "/login":      this->query_type = QUERY_TYPE::LOGIN;       break;
        case "/register":   this->query_type = QUERY_TYPE::REGISTER;    break;
        case "/create":     this->query_type = QUERY_TYPE::CREATE_GAME; break;
        case "/disconnect":
        case "/d":          this->query_type = QUERY_TYPE::DISCONNECT;  break;
        case "/join":       this->joinInput();                          break;
        case "/message":
        case "/msg":        this->messageInput();                       break;
        case "/ranking":
        case "/r":          this->rankingInput();                       break;
        case "/friends":
        case "/f":          this->friendsInput();                       break;
        default:            break;
    }
}

bool MainInputParser::isValidCode(std::string code) {
	if  (code.size() != 4)    { return false; }
	for (auto c : code) { if (not isdigit(c)) return false; }
	return true;
}

void MainInputParser::joinInput() {
    if (this->isValidCode((*this)[1])) { this->query_type = QUERY_TYPE::JOIN_GAME; }
    else { std::cout << "(MainInputParser::joinInput()) Le code n'est pas valide. " << std::endl;}
}

void MainInputParser::messageInput() {
    if (this->getNbParameters() == 2) {
        this->query_type = ((*this)[1] == "show") ? QUERY_TYPE::MESSAGE_SHOW : QUERY_TYPE::MESSAGE_SEND; }
    else { std::cout << "(MainInputParser::messageInput()) Il n'y a pas exactement 2 arguments, il y en a [" << this->getNbParameters() << "]." << std::endl;}
}

void MainInputParser::rankingInput() {
    if (this->getNbParameters() != 1) { return; }
    else if ((*this)[1] == "top") { this->query_type = QUERY_TYPE::RANKING_TOP; }
    else if ((*this)[1] == "pos") { this->query_type = QUERY_TYPE::RANKING_POS; }
    else { std::cout << "(MainInputParser::rankingInput()) Format de la requête incorrect, essayez /ranking {top, pos}" << std::endl;}
}

void MainInputParser::friendsInput() {
    if (this->getNbParameters() < 1)    { return; }
    else if ( (*this)[1] == "list" )    { this->query_type = QUERY_TYPE::FRIENDS_LIST; }
    else if ( (*this)[1] == "request" ) { this->query_type = QUERY_TYPE::FRIENDS_REQUEST; }
    else if ( (*this)[1] == "accept" )  { this->query_type = QUERY_TYPE::FRIENDS_ACCEPT; }
    else if ( (*this)[1] == "refuse" )  { this->query_type = QUERY_TYPE::FRIENDS_REFUSE; }
    else if ( (*this)[1] == "add" )     { this->query_type = QUERY_TYPE::FRIENDS_ADD; }
    else if ( (*this)[1] == "remove" )  { this->query_type = QUERY_TYPE::FRIENDS_REMOVE; }
    else { std::cout << "(MainInputParser::friendsInput()) Aucune commande correspondante." << std::endl;
           std::cout << "Essayez : /friends {list} ou /friends {request, accept, refuse, add, remove} [name]" << std::endl;
    }
}
