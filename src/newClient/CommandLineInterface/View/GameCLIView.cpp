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

void GameCLIView::createGame(JoinInfo2 &info) {
    std::cout << "Vous venez de créer la partie !" << std::endl;
    std::cout << "Le GameCode de la partie actuel est : " << info.game_code << std::endl;
}

void GameCLIView::joinGame(JoinInfo2 &info) {
    std::cout << info.username << " vient de rejoindre la partie possédant le GameCode : " << info.game_code << std::endl;
}

void GameCLIView::startInfo(StartInfo2 &info) {
    std::cout << "La partie vient de débuté c'est au tour de " << info.player_usernames[info.beginner] << " de jouer." << std::endl;
}

void GameCLIView::rollInfo(RollDiceInfo2 &info) {
    std::cout << "Résultat des dés : " << info.first_value << " et " << info.second_value  << std::endl;
    if (info.is_double && info.double_counter < 3) {
        std::cout << "C'est un double, vous allez pouvoir rejouer !" << std::endl;
    }
    std::cout << "Le résultat total est donc " << info.total_value << std::endl;
}

void GameCLIView::infosGame(GameInfoList &info) {
    for (auto player : info.infos) {
        std::cout << "Le joueur " << player.username << " possède " << player.money << "$" << std::endl;
        std::cout << "Iel se trouve sur la position " << player.position << std::endl;
        std::cout << "Voici les propriété qu'iel possède : " << std::endl;
        for (auto prop : player.properties) {
            std::cout << "\t -" << prop.name << std::endl;
        }

    }
}