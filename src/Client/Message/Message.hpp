//
// Created by Rémy Ryckeboer on 10/02/2023.
//

#ifndef INFOF209_SECRET_MESSAGE_HPP
#define INFOF209_SECRET_MESSAGE_HPP

#include <iostream>
using namespace std;

class Message {
public:
    Message()=default;
    void connexionMsg() {
        std::cout << "+------------------------------------------------------------+" << std::endl;
        std::cout << "|Bonjour, bienvenue dans la page de connexion de Capitali$t !|" << std::endl;
        std::cout << "|Se connecter à un compte -> /login [username] [password]    |" << std::endl;
        std::cout << "|Créer un nouveau compte  -> /register [username] [password] |" << std::endl;
        std::cout << "+------------------------------------------------------------+" << std::endl;
    }

    void refuseRegister () {
        std::cout << "+------------------------------------------------------------------------+" << std::endl;
        std::cout << "|La création du compte à échouer, le nom d'utilisateur est déjà utilisé !|" << std::endl;
        std::cout << "+------------------------------------------------------------------------+" << std::endl;
    }

    void refuseLogin() {
        std::cout << "+-------------------------------------------------------+" << std::endl;
        std::cout << "|La connexion à votre compte à échouer, vérifier que :  |" << std::endl;
        std::cout << "|    - Le nom d'utilisateur existe.                     |" << std::endl;
        std::cout << "|    - Le mot de passe est correct.                     |" << std::endl;
        std::cout << "+-------------------------------------------------------+" << std::endl;
    }
    void badConnexionInput() {
        std::cout << "+---------------------------------------------------------+" << std::endl;
        std::cout << "|Please, use one of the three commands below :            |" << std::endl;
        std::cout << "|   /register [username] [password] -> create an account. |" << std::endl;
        std::cout << "|   /login [username] [password] -> log into your account.|" << std::endl;
        std::cout << "|   /disconnect -> leave this application                 |" << std::endl;
        std::cout << "+---------------------------------------------------------+" << std::endl;
    }
};

#endif //INFOF209_SECRET_MESSAGE_HPP
