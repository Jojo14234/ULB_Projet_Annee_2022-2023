//
// Created by Rémy Ryckeboer on 13/02/2023.
//

#ifndef SRC_CONNECTIONUI_HPP
#define SRC_CONNECTIONUI_HPP

#include <iostream>
#include "RegisterUI.hpp"
#include "LoginUI.hpp"

class ConnectionUI : public RegisterUI, public LoginUi {

public:
    void connexionMsg() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|      Bonjour, bienvenue dans la page de connexion de Capitali$t !      |" << std::endl;
        std::cout << "|                                                                        |" << std::endl;
        std::cout << "|      Se connecter à un compte -> /login [pseudo] [mot de passe]        |" << std::endl;
        std::cout << "|      Créer un nouveau compte  -> /register [pseudo] [mot de passe]     |" << std::endl;
        std::cout << "|      Quitter l'application    -> /disconnect                           |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }
    void badConnexionInput() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|      Merci d'utiliser une des commandes présenter ci-dessous :         |" << std::endl;
        std::cout << "|                                                                        |" << std::endl;
        std::cout << "|      Se connecter à un compte -> /login [pseudo] [mot de passe]        |" << std::endl;
        std::cout << "|      Créer un nouveau compte  -> /register [pseudo] [mot de passe]     |" << std::endl;
        std::cout << "|      Quitter l'application    -> /disconnect                           |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }
    void too_short() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|      Vous avez entré un paramètre trop court !                         |" << std::endl;
        std::cout << "|      Taille minimal d'un pseudo       -> 1 caractère                   |" << std::endl;
        std::cout << "|      Taille minimal d'un mot de passe -> 4 caractères                  |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }
    void too_long() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|      Vous avez entré un paramètre trop long !                          |" << std::endl;
        std::cout << "|      Taille maximal d'un pseudo       -> 32 caractères                 |" << std::endl;
        std::cout << "|      Taille maximal d'un mot de passe -> 64 caractères                 |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }
    void banned_char() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|      Vous avez entré un paramètre contenant un caractère interdit !    |" << std::endl;
        std::cout << "|      Voici la liste des caractère interdits : -, +, *, $, &, @, ?, !   |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }

    void disconnect() {
        std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
        std::cout << "|              Vous avez choisis de quitter l'application !              |" << std::endl;
        std::cout << "|              Merci d'avoir joué à notre jeu CAPITALI$T !               |" << std::endl;
        std::cout << "|                    Au plaisir de vous revoir, bye !                    |" << std::endl;
        std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
    }
};

#endif //SRC_CONNECTIONUI_HPP
