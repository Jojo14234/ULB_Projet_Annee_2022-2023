#ifndef _CLIENT_MAIN_INPUT_PARSER_HPP
#define _CLIENT_MAIN_INPUT_PARSER_HPP

#include <vector>
#include <string>

#include "../../utils/Configs.hpp"
#include "InputParser.hpp"

/*
 * Classe permettant de Parser des inputs dans le menu de connection et le menu principale
 * Hérite de la classe `InputParser`
 *
 * MainInputParser(const string &input)
 */
class MainInputParser : public InputParser {

	QUERY_TYPE query_type = QUERY_TYPE::NONE;

   /*
    * This function parses the input string by calling InputParser::parse() function and
    * determines the type of query by examining the first element of the resulting vector.
    * Based on the value of the first element, the function assigns the corresponding value to the `query_type`
    */
	void parse() override;

   /*
    * This function checks whether the input string `code` is a valid code by verifying the following conditions:
    * 1. The length of `code` must be 4.
    * 2. Each character in `code` must be a digit.
    */
	bool isValidCode(std::string code);

   /*
    * This function checks whether the second element of the MainInputParser object, which represents the game code,
    * is a valid code by calling the `isValidCode()` function.
    */
    void joinInput();

   /*
    * This function checks whether the input string has exactly 2 parameters,
    * sets the query type of MainInputParser object based on the second parameter ("show" or "send").
    * Outputs an error message to the console if the parameter count is incorrect.
    */
    void messageInput();

   /*
    * This function validates whether the input string has 1 parameter,
    * and sets `query_type` of MainInputParser object based on the 2nd parameter ("top" or "pos").
    * Outputs an error message if the parameter count or format is incorrect.
    */
    void rankingInput();

   /*
    * This function validates whether the input string has at least 1 parameter
    * and sets `query_type` of MainInputParser object based on the 2nd parameter.
    * If the 2nd parameter is not one of the valid options, outputs an error message.
    */
    void friendsInput();

public:

   /*
    * Constructor of MainInputParser, take a string `Input` as parameters.
    * It directly split and parse it.
    */
	MainInputParser(const std::string &input) : InputParser{input} { this->parse(); }

	// GETTERS
	QUERY_TYPE getQueryType() const { return query_type; }

};

#endif
