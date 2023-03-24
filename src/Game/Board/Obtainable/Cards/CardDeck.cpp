#include <random>
#include <iostream>
#include "CardDeck.hpp"

#include "Card.hpp"
#include "MoneyCard.hpp"
#include "CellCard.hpp"
#include "../../../../utils/Configs.hpp"



CardDeck::CardDeck(std::string name): name{name} {
    // Extraction du deck du fichier Json
    Json::Value root;
    std::ifstream file(CARD_DATA, std::ifstream::binary);
    file >> root;

    // Indexe pour placer les cartes dans l array
    int idx = 0;

    // Extraction de la partie MoneyCard
    Json::Value money_cards = root[name]["MoneyCard"];
    this->extractMoneyCard(money_cards, idx);

    // Extraction de la partie CellCard
    Json::Value cell_cards = root[name]["CellCard"];
    this->extractCellCard(cell_cards, idx);

    // Extraction de la JailCard
    Json::Value jail_card = root[name]["JailCard"];
    this->extractJailCard(jail_card, idx);

}

void CardDeck::extractMoneyCard(Json::Value &cards, int &idx) {

    for (unsigned int i=0; i < cards.size(); i++) {
        // Extraction des données
        std::string description = cards[i]["description"].asString();
        int amount = cards[i]["amount"].asInt();
        int receive = cards[i]["receive"].asInt();

        // Différent type de carte en fonction de la valeur de receive
        switch (receive) {
            case -1: this->card_list[idx] = std::make_shared<FromOtherMoneyCard>(description, amount, true); break;
            case -2: this->card_list[idx] = std::make_shared<ChoiceMoneyCard>(description, amount, false, "LUCKY DECK"); break;
            default: this->card_list[idx] = std::make_shared<MoneyCard>(description, amount, (bool) receive); break;
        }
        // Incrément de l'index pour l array
        idx++;
    }
}

/*
 * Extrait les carte qui font se déplacer le joueur vers une autre case du fichier Json
 * et les place dans le paquet
 */
void CardDeck::extractCellCard(Json::Value &cards, int &idx) {

    for (unsigned int i=0; i < cards.size(); i++) {
        // Extraction des données
        std::string description = cards[i]["description"].asString();
        bool receive_money = cards[i]["money"].asBool();
        int number_destinations = cards[i]["dest"].size();
        int destination = cards[i]["dest"][0].asInt();

        // Si une seule destination négative, moveBackCard
        if ( number_destinations == 1 && destination < 0 ) { this->card_list[idx] = std::make_shared<MoveBackCellCard>(description, receive_money, destination); }
        // Si une seule destination positive, CellCard
        if ( number_destinations == 1 && destination >= 0) { this->card_list[idx] = std::make_shared<CellCard>(description, destination, receive_money); }
        // Si plusieurs destination, NearestStationCard
        if ( number_destinations > 1 ) {
            std::array<int, 4> dest_list;
            for ( unsigned int j=0; j < cards[i]["dest"].size(); j++ ) { dest_list[j] = cards[i]["dest"][j].asInt(); }
            this->card_list[idx] = std::make_shared<NearestCellCard>(description, receive_money, dest_list);
        }
        idx++;
    }
}

/*
 * Extrait la carte Sortie de prison du fichier Json
 * et la place dans le paquet
 */
void CardDeck::extractJailCard(Json::Value &cards, int &idx) {
    // Extraction des donnés
    std::string description = cards["description"].asString();
    // Placement de la carte
    this->card_list[idx] = std::make_shared<JailCard>(description);
}

/*
 * Renvoie la carte tirée au hasard parmi le paquet de 16 carte
 */
Card* CardDeck::drawACard() {
    // Seed pour le hasard pris sur le temps en seconde depuis ...
	std::srand(time(0));
    Card* drawn_card;

    // Boucle tant qu'on n'a pas tiré une carte
	while(!drawn_card) {
		int result = std::rand()% 16;
		drawn_card = this->card_list.at(result).get();
        // Si la carte est le numéro 15, c'est que c'est la carte sortie de prison,
        // et si elle n'est pas dans le paquet il faut retirer une carte
        if (result == 15 && !isJailCardInside()) { drawn_card = nullptr; }
	}
    return drawn_card;
}

/*
 * Renvoie si la carte se trouvant à la position 15, ne possède pas de propriétaire.
 * Si tel est le cas -> la carte est présente dans le paquet (True)
 * Sinon elle n'est pas présente dans le paquet (False)
 */
bool CardDeck::isJailCardInside() {
    return dynamic_cast<JailCard*>(this->card_list.at(15).get())->getOwner() == nullptr;
}

/*
 * Replace la carte dans le paquet en supprimant le pointeur vers son propriétaire
 */
void CardDeck::replaceJailCard() {
    dynamic_cast<JailCard*>(this->card_list.at(15).get())->setOwner(nullptr);
}