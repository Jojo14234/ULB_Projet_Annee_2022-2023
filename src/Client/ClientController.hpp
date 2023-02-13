#ifndef _CLIENT_CONTROLLER_HPP
#define _CLIENT_CONTROLLER_HPP

#include <iostream>
#include <string>


class ClientController {

    std::string input;

public:

    std::string getInput() { return this->input; }

    std::string getNewInput() {
        std::cout << "> ";
        std::getline(std::cin, this->input);
        return input;
    }

};

#endif
