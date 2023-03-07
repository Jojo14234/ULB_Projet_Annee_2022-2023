#ifndef _CLIENT_INPUT_PARSER_HPP
#define _CLIENT_INPUT_PARSER_HPP

#include <vector>
#include <iostream>
#include <string>


class InputParser {

private:

	const std::string input;
	std::vector<std::string> input_splited;
	
	// Split the input to a list of string seperate by a ' '
    void split() {
		input_splited.clear();
		std::string str;	
		for ( char e : this->input ) { 
			if ( e == ' ' ) { this->input_splited.push_back(str); str=""; }
			else { str += e; }
		} this->input_splited.push_back(str);
	}

protected:

	// Parse the input from the client
	virtual void parse() { this->split(); }

public:

	InputParser(const std::string &input) : input{input} { this->parse(); }
	virtual ~InputParser()=default;

	// The n parameter from the input_splited
	const std::string &operator[](int n) const { return this->input_splited[n]; }

	// The nb of parameters (does not count the query type ex : /login remy rkb -> 2, not 3)
	int getNbParameters() const { return input_splited.size() - 1; }

    void regroupParameters() {
        std::string merged_params = "";
        // Loop over the params of the loop (but not the last)
        for (unsigned int i = 1; i < input_splited.size() - 1; i++) {
            merged_params += input_splited[i]; // add the params to the `regroup_params` variable
            merged_params += " "; // Add a space between each params
        }
        merged_params += input_splited[input_splited.size()-1]; // Add the last params but without the space at the end.
        input_splited[1] = merged_params; // Place the `regroup_params` variable at the place of the first params.
    }
};

#endif
