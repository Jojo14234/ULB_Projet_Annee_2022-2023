#ifndef _CLIENT_LOGINUI_HPP
#define _CLIENT_LOGINUI_HPP

#include <iostream>


class LoginUi {
public:
    void refuseLogin() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|                La connexion à votre compte à échouer !                 |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }

    void acceptLogin() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|                La connexion à votre compte a réussis !                 |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }
};

#endif