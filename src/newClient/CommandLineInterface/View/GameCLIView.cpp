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
    std::cout << "La partie vient de débuter c'est au tour de " << info.player_usernames[info.beginner] << " de jouer." << std::endl;
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

void GameCLIView::newTurn(std::string username) {
    std::cout << "Nouveau tour ! C'est à de " << username << " de jouer." << std::endl;
}

void GameCLIView::moveOn(PlayerMoveInfo2 &info) {
    std::cout << "Le joueur "<< info.player <<" vient d'arriver sur la case :" << info.property_name << " !" << std::endl;
}

void GameCLIView::buyProp(PlayerMoveInfo2 &info) {
    std::cout << "Le joueur "<< info.player <<" vient d'acheter la case :" << info.property_name << " !" << std::endl;
}

void GameCLIView::didntBuy(std::string username) {
    std::cout << "Le joueur "<< username <<" vient de refuser d'acheter une propriété. " << std::endl;
}

void GameCLIView::playerPaidPlayer(PlayerPaidPlayerInfo2 &info) {
    std::cout << "Le joueur " << info.loser << " à payer " << info.amount << "€ à " << info.winner << std::endl;
}

void GameCLIView::mortgagedCellMoveOn(MoveMortgagedInfo2 &info) {
    std::cout << "Le joueur " << info.username << " vient d'arrivez sur une propriété hypothéquer par "<< info.owner_username <<". Iel ne paye donc pas de loyer" << std::endl;
 }

 void GameCLIView::ownCellMoveOn(std::string username) {
    std::cout << "Le joueur " << username << " vient d'arriver chez lui !" << std::endl;
}

void GameCLIView::taxCellMoveOn(MoveTaxInfo2 &info) {
    std::cout << "Le joueur " << info.player << " est tombé sur la taxe " << info.tax_name << " et doit payer " << info.price << "€" << std::endl;
}

void GameCLIView::askPurchase(AskForPurchaseInfo2 &info) {
    std::cout << "Vous avez la possibilité d'acheter la case : " << info.cell_name << " pour la somme de " << info.amount << "€" << std::endl;
    std::cout << " - Faites /yes pour accepter et payer" << std::endl;
    std::cout << " - Faites /no pour refuser et mettre la propriété aux enchères" << std::endl;
}

void GameCLIView::getInJail(std::string username) {
    std::cout << "Le joueur " << username << " va en prison !" << std::endl;
}

void GameCLIView::getOutJail(std::string username) {
    std::cout << "Le joueur " << username << " sort de prison !" << std::endl;
}

void GameCLIView::getOutJailCard(std::string username) {
    std::cout << "Le joueur " << username << " à reçu une carte sortie de prison !" << std::endl;
}

void GameCLIView::UseOutJailCard(std::string username) {
    std::cout << "Le joueur " << username << " utilise sa carte sortie de prison !"<< std::endl;
}

void GameCLIView::gainMoney(WonOrLoseMoneyInfo2 &info) {
    std::cout << "Le joueur " << info.player << " vient de recevoir " << info.amount << "€. Son compte est désormais à " << info.player_money << "€" << std::endl;
}

void GameCLIView::looseMoney(WonOrLoseMoneyInfo2 &info) {
    std::cout << "Le joueur" << info.player << " vient de perdre " << info.amount << "€. Son compte est désormais à " << info.player_money << "€" << std::endl;
}

void GameCLIView::drawCardMoveOn(MoveOnCardCellInfo2 &info) {
    std::cout << "Le joueur " << info.player <<" vient de piocher la carte suivante" << std::endl;
    std::cout << "\t" << info.description << std::endl;
}

void GameCLIView::drawCardMoveOn(std::string description) {
    std::cout << "Le joueur vient de piocher la carte suivante" << std::endl;
    std::cout << "\t" << description << std::endl;
}

void GameCLIView::joinBuildMode(BuildOrSellList &info) {
    std::cout << "Vous êtes dans le mode construction. Voici les propriété sur lesquelles vous pouvez construire :" << std::endl;
    for (auto prop : info.properties) {
        std::cout << prop << std::endl;
    }
    std::cout << "Choisissez la propriété en faisant /select [property_name]" << std::endl;
    std::cout << "Pour quittez le mode de construction faites /leave" << std::endl;
}

void GameCLIView::joinSellMode(BuildOrSellList &info) {
    std::cout << "Vous êtes dans le mode vente. Voici les propriété sur lesquelles vous pouvez vendre :" << std::endl;
    for (auto prop : info.properties) {
        std::cout << prop << std::endl;
    }
    std::cout << "Choisissez la propriété en faisant /select [property_name]" << std::endl;
    std::cout << "Pour quittez le mode de construction faites /leave" << std::endl;
}

void GameCLIView::leaveMode() {
    std::cout << "Vous quittez le mode dans lequel vous étiez" << std::endl;
}

void GameCLIView::propInfos(BuildSuccessInfo2 &info) {
    std::cout << "La propriété " << info.name << " est de niveau " << info.level << std::endl;
}

void GameCLIView::notEnoughMoney() {
    std::cout << "Vous n'avez pas assez d'argent" << std::endl;
}

void GameCLIView::cannotBuild() {
    std::cout << "Vous ne pouvez pas construire ici !" << std::endl;
}

void GameCLIView::dontHavePropBuildable() {
    std::cout << "Vous n'avez pas de propriété permettant la construction !" << std::endl;
}

void GameCLIView::choiceMoneyCard() {
    std::cout << "Vous devez choisir entre payer ou piocher une autre carte." << std::endl;
    std::cout << " - Payer : /pay" << std::endl;
    std::cout << " - Piocher : /card" << std::endl;
}