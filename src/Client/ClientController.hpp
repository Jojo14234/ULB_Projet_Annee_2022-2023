//
// Created by Rémy Ryckeboer on 13/02/2023.
//

#ifndef SRC_CLIENTCONTROLLER_HPP
#define SRC_CLIENTCONTROLLER_HPP

#include <iostream>
#include <string>

class ClientController {
    std::string input;
public:
    ClientController() =default;
    std::string getInput() {return input;}
    std::string getNewInput() {
        std::cout << "> ";
        std::getline(std::cin, this->input);
        return input;
    }
};

#endif //SRC_CLIENTCONTROLLER_HPP
