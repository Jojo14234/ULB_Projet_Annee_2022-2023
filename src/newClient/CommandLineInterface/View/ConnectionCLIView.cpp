//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#include <iostream>

#include "ConnectionCLIView.hpp"

void ConnectionCLIView::draw() {
    std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
    std::cout << "|      Bonjour, bienvenue dans la page de connexion de Capitali$t !      |" << std::endl;
    std::cout << "|                                                                        |" << std::endl;
    std::cout << "|      Se connecter à un compte -> /login [pseudo] [mot de passe]        |" << std::endl;
    std::cout << "|      Créer un nouveau compte  -> /register [pseudo] [mot de passe]     |" << std::endl;
    std::cout << "|      Quitter l'application    -> /disconnect                           |" << std::endl;
    std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
}

void ConnectionCLIView::draw2() {
    //to avoid unused parameter
}