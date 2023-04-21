//
// Created by Rémy Ryckeboer on 29/03/2023.
//

#ifndef INFO_F209_GR5_2022_CONNECTIONINPUTPARSER_HPP
#define INFO_F209_GR5_2022_CONNECTIONINPUTPARSER_HPP

#include "InputParser.hpp"

enum class CONNECTION_QUERY {LOGIN, REGISTER, DISCONNECT, OTHER};


class ConnectionInputParser : public InputParser {

    CONNECTION_QUERY query = CONNECTION_QUERY::OTHER;

public:
    ConnectionInputParser(std::string input): InputParser{input} { this->parse(); }

    void parse() {
        this->split();

        std::string query = this->inputs[0];
        if      ( query == "/login" )     { this->query = CONNECTION_QUERY::LOGIN; }
        else if ( query == "/register" )  { this->query = CONNECTION_QUERY::REGISTER; }
        else if ( query == "/disconnect" ){ this->query = CONNECTION_QUERY::DISCONNECT; }
        else                              { this->query = CONNECTION_QUERY::OTHER; }
    }

    CONNECTION_QUERY getQuery() const { return this->query; }
};

#endif //INFO_F209_GR5_2022_CONNECTIONINPUTPARSER_HPP
