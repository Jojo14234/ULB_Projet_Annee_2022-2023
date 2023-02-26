#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <iostream>
#include <string>


class Client{

public:

	void sendLogin(std::string username, std::string password) {
		std::cout << "Client::sendLogin()" << std::endl;
		std::cout << "Username: " << username << std::endl;
		std::cout << "Password: " << password << std::endl;
	}

	void sendRegister(std::string username, std::string password) {
		std::cout << "Client::sendRegister()" << std::endl;
		std::cout << "Username: " << username << std::endl;
        std::cout << "Password: " << password << std::endl;
    }


};

#endif