//
// Created by Rémy Ryckeboer on 13/02/2023.
//

#ifndef SRC_AUTHENTIFICATIONMANAGER_HPP
#define SRC_AUTHENTIFICATIONMANAGER_HPP

#include <string>
#include "../utils/Configs.hpp"
#include "./UI/ConnectionUI.hpp"

// AuthentificationManager Infos status
enum PARAMS_STATUS {
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
    AuthentificationManager(std::string username, std::string password): username{username}, password{password} {checkValidity();};
    void checkValidity() {
        status = SUCCESSFUL;
        if (!checkUsernameValidity()) {return;}
        if (!checkPasswordValidity()) {return;}
    }

    bool checkUsernameValidity() {
        if (username_min_length > username.length()) {status = PARAMS_STATUS::USERNAME_TOO_SHORT; return false;}
        if (username_max_length < username.length()) {status = PARAMS_STATUS::USERNAME_TOO_LONG; return false;}
        for (auto banned_char : banned_character) {
            if (username.find(banned_char) != std::string::npos) {status = PARAMS_STATUS::USERNAME_BANNED_CHAR; return false;}
        }
        return true;
    }

    bool checkPasswordValidity() {
        if (password_min_length > password.length()) {status = PARAMS_STATUS::PASSWORD_TOO_SHORT; return false;}
        if (password_max_length < password.length()) {status = PARAMS_STATUS::PASSWORD_TOO_LONG; return false;}
        for (auto banned_char : banned_character) {
            if (password.find(banned_char) != std::string::npos) {status = PARAMS_STATUS::PASSWORD_BANNED_CHAR; return false;}
        }
        return true;
    }

    bool isValid() {return status == PARAMS_STATUS::SUCCESSFUL;}

    void showErrorMessage(ConnectionUI &ui) {
        switch (this->status) {
            case USERNAME_TOO_SHORT:
            case PASSWORD_TOO_SHORT:
                ui.too_short();
                break;
            case USERNAME_TOO_LONG:
            case PASSWORD_TOO_LONG:
                ui.too_long();
                break;
            case USERNAME_BANNED_CHAR:
            case PASSWORD_BANNED_CHAR:
                ui.banned_char();
                break;
            case SUCCESSFUL:
            default:
                break;
        }
    }
};

#endif //SRC_AUTHENTIFICATIONMANAGER_HPP
