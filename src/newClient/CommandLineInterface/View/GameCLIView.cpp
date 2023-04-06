//
// Created by Rémy Ryckeboer on 30/03/2023.
//
#include <iostream>

#include "GameCLIView.hpp"

void GameCLIView::draw() {
    std::cout << "+———————————————————————————————CAPITALI$T———————————————————————————————+" << std::endl;
    std::cout << "|             Liste des commandes disponibles dans la partie :           |" << std::endl;
    std::cout << "|                                                                        |" << std::endl;
    std::cout << "|      - Lancer les dés -> /roll                                         |" << std::endl;
    std::cout << "|      - Acheter un bâtiment -> /build + /select [property]              |" << std::endl;
    std::cout << "|      - Vendre un bâtiment  -> /sell + /select [property]               |" << std::endl;
    std::cout << "|      - Hypothéquer -> /mortgage + /select [property]                   |" << std::endl;
    std::cout << "|      - Déshypothéquer -> /liftmortgage + /select [property]            |" << std::endl;
    std::cout << "|      - Faire un échange -> /exchange + /trade [property] [money]       |" << std::endl;
    std::cout << "+————————————————————————————————————————————————————————————————————————+" << std::endl;
}

void GameCLIView::draw2() {
    // to avoid unused view in GameCLIController
}