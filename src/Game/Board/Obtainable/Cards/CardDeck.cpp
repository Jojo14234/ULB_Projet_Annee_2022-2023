
#include <random>

#include "CardDeck.hpp"
#include "Card.hpp"
#include "MoneyCard.hpp"
#include "CellCard.hpp"
#include "JailCard.hpp"
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
        std::string type = cards[i]["type"].asString();

        // Parsing des cartes
        if      (type == "Money")    { this->card_list[idx] = std::make_shared<MoneyCard2>(description, amount); }
        else if (type == "Birthday") { this->card_list[idx] = std::make_shared<FromOtherMoneyCard>(description, amount); }
        else if (type == "Choice")   { this->card_list[idx] = std::make_shared<ChoiceMoneyCard>(description, amount, "LUCKY DECK"); }
        else if (type == "HouseHotel") {
            int house_price = cards[i]["params"][0].asInt();
            int hotel_price = cards[i]["params"][1].asInt();
            this->card_list[idx] = std::make_shared<HouseHotelMoneyCard>(description, amount, house_price, hotel_price);
        }
        else { continue; }
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
        int destination = cards[i]["dest"][0].asInt();
        std::string type = cards[i]["type"].asString();

        if      ( type == "Cell" )     { this->card_list[idx] = std::make_shared<CellCard>(description, destination, receive_money); }
        else if ( type == "Stations" ) { this->card_list[idx] = std::make_shared<NearestCellCard>(description, receive_money, this->extractStationsArray(cards[i]));}
        else                           { continue; }
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
 * Extrait les 4 position des gares et les renvoie un array les contenants
 */
std::array<int, 4> CardDeck::extractStationsArray(Json::Value &cards) {
    std::array<int, 4> stations;
    for (unsigned int j = 0; j < cards["dest"].size(); j++) {
        stations[j] = cards["dest"][j].asInt();
    }
    return stations;
}

/*
 * Renvoie la carte tirée au hasard parmi le paquet de 16 carte
 */
Card* CardDeck::drawACard() {
    // Seed pour le hasard pris sur le temps en seconde depuis ...
	std::srand(time(0));
    Card* drawn_card = nullptr;

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