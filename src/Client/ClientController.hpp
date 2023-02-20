#ifndef _CLIENT_CONTROLLER_HPP
#define _CLIENT_CONTROLLER_HPP

#include <iostream>
#include <string>

#include "InputParser/MainInputParser.hpp"
#include "InputParser/GameInputParser.hpp"


class ClientController {

	std::string input;

	void setInput() {
		std::cout << "> ";
		std::getline(std::cin, this->input);
	}

public:

	// GETTERS

	std::string getInput() { return this->input; }

	std::string getNewInput() {
		this->setInput();
		return input;
	}

	MainInputParser getNewParsedInput() {
		this->setInput();
		std::cout << "Vous venez d'entrer : " << input << std::endl;
		return MainInputParser{input};
	}

	GameInputParser getNewGameParsedInput() {
		this->setInput();
		std::cout << "Vous venez d'entrer : " << input << std::endl;
		return GameInputParser{input};
	}

};

#endif
