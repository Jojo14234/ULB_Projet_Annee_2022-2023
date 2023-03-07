#ifndef _CLIENT_AUTHENTIFICATION_MANAGER_HPP
#define _CLIENT_AUTHENTIFICATION_MANAGER_HPP

#include <string>

#include "../utils/Configs.hpp"
#include "UI/ConnectionUI.hpp"


/*
 * This code defines an enumerated type called `PARAMS_STATUS` that contains the possible status values that an AuthenticationManager object can have.
 * These values represent the validity of username and password parameters that are passed to the AuthenticationManager object.
 * The possible status values are:
 * - USERNAME_TOO_LONG :   The username is too long.
 * - USERNAME_TOO_SHORT :  The username is too short.
 * - USERNAME_BANNED_CHAR: The username contains banned characters.
 * - PASSWORD_TOO_LONG :   The password is too long.
 * - PASSWORD_TOO_SHORT :  The password is too short.
 * - PASSWORD_BANNED_CHAR: The password contains banned characters.
 * - SUCCESSFUL :          The username and password parameters are valid.
 */
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
    /*
     * Constructor of AuthentificationManager, it takes 2 strings `username` and `password` as parameters.
     * It stores the value and check if they are valid, it stores the validity status in a variable called status.
     */
	AuthentificationManager(std::string username, std::string password): username{username}, password{password} { this->checkValidity(); }

   /*
    * Set the `status` to SUCCESSFUL and then check if `username` and `password` are valid
    */
	void checkValidity();

   /*
    * Return whether or not the `username` is valid in terms of length and authorized characters.
    * If it's not valid it set the `status` to the corresponding value
    */
	bool checkUsernameValidity();

   /*
    * Return whether or not the `password` is valid in terms of length and authorized characters.
    * If it's not valid it set the `status` to the corresponding value
    */
	bool checkPasswordValidity();

   /*
    * Return whether or not teh `status` is successful
    */
    bool isValid() { return this->status == PARAMS_STATUS::SUCCESSFUL; }

   /*
    * Show the correct error message in the UI
    * The message depends on the `status` attributs
    */
    void showErrorMessage(ConnectionUI &ui);
};

#endif