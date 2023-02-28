#ifndef _CLIENT_REGISTERUI_HPP
#define _CLIENT_REGISTERUI_HPP

#include <iostream>


class RegisterUI {
public:
    void refuseRegister() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|La création du compte à échouer, le nom d'utilisateur est déjà utilisé !|" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }

    void acceptRegister() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|                    La création du compte à réussi !                    |" << std::endl;
        std::cout << "|     Vous avez été automatiquement connecté à votre nouveau compte.     |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }
};


#endif