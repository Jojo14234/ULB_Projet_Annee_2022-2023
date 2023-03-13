#ifndef _CLIENT_CONTROLLER_HPP
#define _CLIENT_CONTROLLER_HPP

#include <iostream>
#include <string>

#include "InputParser/MainInputParser.hpp"
#include "InputParser/GameInputParser.hpp"


class ClientController {

	std::string input;

   /*
    * Method that show an '>' and wait for an input from the user
    */
	void setInput() {
		std::cout << "> ";
		std::getline(std::cin, this->input);
	}

public:

    /*
     * Methode that return the new input from the user
     */
	std::string getNewInput() {
		this->setInput();
        std::cout << "Vous venez d'entrer : " << input << " none parsed" << std::endl;
		return input;
	}

    /*
     * Method that return a `MainInputParser` object that contains the user input parsed.
     */
	MainInputParser getNewParsedInput() {
		this->setInput();
		std::cout << "Vous venez d'entrer : " << input << " parsed by MainInputParser" << std::endl;
		return MainInputParser{input};
	}

    /*
    * Method that return a `GameInputParser` object that contains the user input parsed.
    */
	GameInputParser getNewGameParsedInput() {
		this->setInput();
		std::cout << "Vous venez d'entrer : " << input << " parsed by GameInputParser" << std::endl;
		return GameInputParser{input};
	}

    // GETTERS
    std::string getInput() { return this->input; }

};

#endif
