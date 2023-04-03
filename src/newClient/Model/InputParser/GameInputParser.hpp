/**
 * Project Untitled
 */

#pragma once

#include <vector>
#include <string>

#include "../../../utils/Configs.hpp"
#include "InputParser.hpp"


class GameInputParser : public InputParser {

	GAME_QUERY_TYPE query_type = GAME_QUERY_TYPE::NONE;

	void parse() override {
        this->split();

        const std::string query = this->inputs[0];
        if      ( query == "/start" )       { this->query_type = GAME_QUERY_TYPE::START; }          // Démarre la partie
        else if ( query == "/roll" )        { this->query_type = GAME_QUERY_TYPE::ROLL_DICE; }      // Lance les dés
        else if ( query == "/pay" )         { this->query_type = GAME_QUERY_TYPE::PAY; }            // To pay to exit prison
        else if ( query == "/card" )        { this->query_type = GAME_QUERY_TYPE::CARD; }           // Pioche une carte lors qu'on a piocher la carte choix
        else if ( query == "/use" )         { this->query_type = GAME_QUERY_TYPE::USEGOOJCARD; }    // To use the card get out of jail
        else if ( query == "/select")       { 
            if (this->size() >= 2)          { this->query_type = GAME_QUERY_TYPE::SELECT; } 
        }
        else if ( query == "/leave" )       { this->query_type = GAME_QUERY_TYPE::LEAVE_SELECTION; }// Quitte la sélection
        else if ( query == "/build" )       { this->query_type = GAME_QUERY_TYPE::BUILD; }          // passer en mode construction
        else if ( query == "/sell" )        { this->query_type = GAME_QUERY_TYPE::SELL_BUILDINGS; } // passer en mode vente
        else if ( query == "/mortgage" )    { this->query_type = GAME_QUERY_TYPE::MORTGAGE; }       // Passe en mode hypothèque
        else if ( query == "/liftMortgage" ){ this->query_type = GAME_QUERY_TYPE::LIFT_MORTGAGE; }  // Passer en mode lift hypothèque
        else if ( query == "/exchange" )    { this->query_type = GAME_QUERY_TYPE::EXCHANGE;}        // Commence un échange
        else if ( query == "/yes" )         { this->query_type = GAME_QUERY_TYPE::YES; }            // C'est un oui
        else if ( query == "/no" )          { this->query_type = GAME_QUERY_TYPE::NO; }             // C'est un non
        else if ( query == "/accept" )      { this->query_type = GAME_QUERY_TYPE::ACCEPT; }         // refuser
        else if ( query == "/refuse" )      { this->query_type = GAME_QUERY_TYPE::REFUSE; }         // accepter
        else if ( query == "/participate" ) { this->query_type = GAME_QUERY_TYPE::PARTICIPATE; }    // Participe à une enchère
        else if ( query == "/trade" )       {
            if (this->size() >= 2 )         { this->query_type = GAME_QUERY_TYPE::TRADE; }
        }
        else                                { this->query_type = GAME_QUERY_TYPE::NONE; }
    }

public:

	GameInputParser(const std::string &input) : InputParser{input} { this->parse(); }
	
	GAME_QUERY_TYPE getQuery() const { return query_type; }

};