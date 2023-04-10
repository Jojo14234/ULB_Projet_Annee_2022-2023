//
// Created by Rémy Ryckeboer on 30/03/2023.
//

#include <iostream>
#include "MenuCLIView.hpp"

void MenuCLIView::draw() {
    std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
    std::cout << "|             Liste des commandes disponibles dans le menu :             |" << std::endl;
    std::cout << "|                                                                        |" << std::endl;
    std::cout << "|                               CREATION                                 |" << std::endl;
    std::cout << "|              Créer une partie -> /create [normale/fast]                |" << std::endl;
    std::cout << "|                                                                        |" << std::endl;
    std::cout << "|                               REJOINDRE                                |" << std::endl;
    std::cout << "|             Rejoindre une partie -> /join [gameCode]                   |" << std::endl;
    std::cout << "|                                                                        |" << std::endl;
    std::cout << "|                              CLASSEMENT                                |" << std::endl;
    std::cout << "|              Voir le classement -> /rank [top/pos]                     |" << std::endl;
    std::cout << "|                                                                        |" << std::endl;
    std::cout << "|                              LISTE D'AMIS                              |" << std::endl;
    std::cout << "|              Voir sa list d'amis -> /friends list                      |" << std::endl;
    std::cout << "|          Gérer ses amis -> /friends [add/remove] [username]            |" << std::endl;
    std::cout << "|     Gérer ses demande d'amis -> /friends [accept/refuse] [username]    |" << std::endl;
    std::cout << "|                                                                        |" << std::endl;
    std::cout << "|                               MESSAGES                                 |" << std::endl;
    std::cout << "|         Envoyer un message privée -> /msg [username] [message]         |" << std::endl;
    std::cout << "|         Voir sa conversation -> /msg [show] [username]                 |" << std::endl;
    std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
}
