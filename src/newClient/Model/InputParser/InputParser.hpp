/**
 * Project Untitled
 */

#pragma once

#include <vector>
#include <iostream>
#include <string>


class InputParser {

protected:

	const std::string input;
	std::vector<std::string> input_splited;

   /*
	* Belong to InputParser classe.
	* This function splits the input string by space (' ') character and stores the resulting substrings in a vector of strings called `input_separated`.
	* It clears the `input_separated` vector before splitting the input string.
	*/
	void split() {
		input_splited.clear();
		std::string str;	
		for ( char e : this->input ) { 
			if ( e == ' ' ) { this->input_splited.push_back(str); str=""; }
			else { str += e; }
		} this->input_splited.push_back(str);
	}

	/*
	 * Belongs to InputParser
	 * Called in the constructor.
	 * Actually does not parse but, split the Input with InputParser::split();
	 */
	virtual void parse() { this->split(); }

public:

	/*
	* Constructor of InputParser, take a string `Input` as parameters.
	* It stores it in variable `input`. Splits and stores it vector `input_separated`
	*/
	InputParser(const std::string &input) : input{input} { this->parse(); }
	virtual ~InputParser()=default;

	/*
	 * This code defines a method that provides a convenient way to access elements of the parsed input string vector by overloading the `[]` operator.
	 * The method takes an integer as a parameter and returns a constant reference to the corresponding element of the `input_separated` vector.
	 */
	const std::string &operator[](int n) const { return this->input_splited[n]; }

	/*
	 * This function return the number of parameters in the input.
	 * It doesn't count the query field. (e.g. : /login [username] [password] have 2 parameters)
	 */
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