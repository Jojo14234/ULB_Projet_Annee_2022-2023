#ifndef _INPUT_PARSER_HPP
#define _INPUT_PARSER_HPP

#include <vector>
#include <string>

#include "../utils/Configs.hpp"


class InputParser {

	const std::string input;
	std::vector<std::string> input_splited;
	QUERY_TYPE query_type;
	
	// Parse the input from the client
	void parse();

	// Split the input to a list of string seperate by a ' '
    void split();

public:

	InputParser(const std::string &input) : input{input} { this->parse(); }
	
	QUERY_TYPE getQueryType() const { return query_type; }
    
	// The nb of parameters (does not count the query type ex : /login remy rkb -> 2, not 3)
    int getNbParameters() const { return input_splited.size() - 1; }
    
	// The n parameter from the input_splited
	const std::string &operator[](int n) const;
};

#endif
