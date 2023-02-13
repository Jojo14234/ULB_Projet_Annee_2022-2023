//
// Created by Rémy Ryckeboer on 13/02/2023.
//

#ifndef SRC_REGISTERUI_HPP
#define SRC_REGISTERUI_HPP

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


#endif //SRC_REGISTERUI_HPP
