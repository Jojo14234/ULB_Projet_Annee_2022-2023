#include "GameInputParser.hpp"

void GameInputParser::parse() {
	InputParser::parse();
	const std::string &query = (*this)[0];

	if      ( query == "/roll" )        { this->query_type = GAME_QUERY_TYPE::ROLL_DICE; } // Lance les dés
    else if ( query == "/out" )         { this->query_type = GAME_QUERY_TYPE::LEAVE_BID; } // Quitte une enchère
    else if ( query == "/mortgage" )    { this->query_type = GAME_QUERY_TYPE::MORTGAGE; }  // Passe en mode hypothèque
    else if ( query == "/demortgage")   { this->query_type = GAME_QUERY_TYPE::DEMORTGAGE; }
    else if ( query == "/leave" )       { this->query_type = GAME_QUERY_TYPE::LEAVE_SELECTION_MODE; } // Qui la sélection
    else if ( query == "/exchange" )    { this->query_type = GAME_QUERY_TYPE::EXCHANGE;}   // Commence un échange
    else if ( query == "/build" )       { this->query_type = GAME_QUERY_TYPE::BUILD; }     // Construit un/des bâtiment(s)
    else if ( query == "/sell" )        { this->query_type = GAME_QUERY_TYPE::SELL_BUILDINGS; } // Vend un/des bâtiment(s)
    else if ( query == "/give-up" )     { this->query_type = GAME_QUERY_TYPE::GIVE_UP; }   // Abandonne
    else if ( query == "/participate" ) { this->query_type = GAME_QUERY_TYPE::PARTICIPATE; } // Participe à une enchère
    else if ( query == "/start" )       { this->query_type = GAME_QUERY_TYPE::START; }     // Démarre la partie
    else if ( query == "/end" )         { this->query_type = GAME_QUERY_TYPE::END_TURN; }  // Termine son tour
    else if ( query == "/leave" )       { this->query_type = GAME_QUERY_TYPE::LEAVE; }     // Quitte la partie
	else if ( query == "/buy" )         { this->query_type = GAME_QUERY_TYPE::BUY; }       // Achète une propriété
	else if ( query == "/disconnect" )  { this->query_type = GAME_QUERY_TYPE::LEAVE; }     // Quitte la partie
    else if ( query == "/accept")       { this->query_type = GAME_QUERY_TYPE::ACCEPT; }    //accepte de participer à l'échange

    else if ( query == "/bid") {
        if ( this->getNbParameters() == 1 ) { this->query_type = GAME_QUERY_TYPE::BID; }   // Enchéri d'un certain montant
        else { std::cout << "Le format de la requête doit être /bid [amount]" << std::endl; }
    }
    else if ( query == "/select" ) {
        if ( this->getNbParameters() >= 1 ) {this->query_type = GAME_QUERY_TYPE::SELECT; regroupParameters(); }
        else { std::cout << "Le format de la requête doit être /select [données]" << std::endl; }
    }
    else if ( query == "/arg1" ) {
        if ( this->getNbParameters() == 1 ) { this->query_type = GAME_QUERY_TYPE::ARG1; }   // Arguments numéro 1
        else { std::cout << "(GameInputParser::parse(/arg1)) cependant il y a [" << this->getNbParameters() << "] argument(s) !" << std::endl; }
    }
    else if ( query == "/arg2" ) {
        if ( this->getNbParameters() == 2 ) { this->query_type = GAME_QUERY_TYPE::ARG2; }   // Argument numéro 2
        else { std::cout << "(GameInputParser::parse(/arg2)) cependant il y a [" << this->getNbParameters() << "] argument(s) !" << std::endl; }
    }
    else { std::cout << "(GameInputParser::parse(...)), commande non reconnue !" << std::endl; } // Autre
}
