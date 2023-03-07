#include "AuthentificationManager.hpp"


// Public
void AuthentificationManager::checkValidity() {
	this->status = PARAMS_STATUS::SUCCESSFUL;
	if (!this->checkUsernameValidity()) { return; }
	if (!this->checkPasswordValidity()) { return; }
}

bool AuthentificationManager::checkUsernameValidity() {
    // Check Min length
	if ( username_min_length > this->username.length() ) {
		this->status = PARAMS_STATUS::USERNAME_TOO_SHORT; 
		return false; }

    //Check Max length
    if ( username_max_length < this->username.length() ) {
		this->status = PARAMS_STATUS::USERNAME_TOO_LONG;
		return false; }

    // Check authorized characters
	for ( auto banned_char : banned_character ) {
		if (this->username.find(banned_char) != std::string::npos) {
			this->status = PARAMS_STATUS::USERNAME_BANNED_CHAR;
			return false; }
	}
	return true;
}

bool AuthentificationManager::checkPasswordValidity() {
    // Check Min length
	if ( password_min_length > this->password.length() ) {
		this->status = PARAMS_STATUS::PASSWORD_TOO_SHORT;
		return false; }

    //Check Max length
    if ( password_max_length < this->password.length() ) {
		this->status = PARAMS_STATUS::PASSWORD_TOO_LONG;
		return false; }

    // Check authorized characters
	for ( auto banned_char : banned_character ) {
		if ( this->password.find(banned_char) != std::string::npos ) {
			this->status = PARAMS_STATUS::PASSWORD_BANNED_CHAR;
			return false; }
	}
	return true;
}


void AuthentificationManager::showErrorMessage(ConnectionUI &ui) {
	switch (this->status) {
		case PARAMS_STATUS::USERNAME_TOO_SHORT:
		case PARAMS_STATUS::PASSWORD_TOO_SHORT:   ui.too_short(); break;
		case PARAMS_STATUS::USERNAME_TOO_LONG:
		case PARAMS_STATUS::PASSWORD_TOO_LONG:    ui.too_long(); break;
		case PARAMS_STATUS::USERNAME_BANNED_CHAR:
		case PARAMS_STATUS::PASSWORD_BANNED_CHAR: ui.banned_char(); break;
		case PARAMS_STATUS::SUCCESSFUL:
		default: break;
	}
}
