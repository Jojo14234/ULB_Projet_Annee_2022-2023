#ifndef _CLIENT_AUTHENTIFICATION_MANAGER_HPP
#define _CLIENT_AUTHENTIFICATION_MANAGER_HPP

#include <string>

#include "../utils/Configs.hpp"
#include "UI/ConnectionUI.hpp"


// AuthentificationManager Infos status
enum class PARAMS_STATUS {
	USERNAME_TOO_LONG,
	USERNAME_TOO_SHORT,
	USERNAME_BANNED_CHAR,
	PASSWORD_TOO_LONG,
	PASSWORD_TOO_SHORT,
	PASSWORD_BANNED_CHAR,
	SUCCESSFUL
};


class AuthentificationManager {

	std::string username;
	std::string password;
	PARAMS_STATUS status = PARAMS_STATUS::SUCCESSFUL;

public:
	
	AuthentificationManager(std::string username, std::string password): username{username}, password{password} { this->checkValidity(); }
	
	// Check Validity
	void checkValidity();
	bool checkUsernameValidity();
	bool checkPasswordValidity();

	// If unsername and password are valid
	bool isValid() { return this->status == PARAMS_STATUS::SUCCESSFUL; }

	// Show the error message on specific UI
	void showErrorMessage(ConnectionUI &ui);
};

#endif