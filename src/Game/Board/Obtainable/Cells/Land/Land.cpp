#include "../../../../Player/Player.hpp"
#include "Land.hpp"
#include "Property.hpp"
#include "Company.hpp"
#include "Station.hpp"


/*
 * Met en hypothèque une propriété et donne la moitié du prix d'achat au player
 */
void Land::mortgage(Player* player){
	this->status = LAND_STATUS::HYPOTEK;
    player->receive(purchase_price/2, "hypothèque");
}

/*
 * Le `player` rachète la propriété qui était en hypothèque et la paye moitié prix
 */
void Land::liftMortgage(Player *player) {
    if ( player->pay(purchase_price/2) ) { this->status = LAND_STATUS::PAID; }
}
/*
 * Pay le Land et marque owner comme étant le player, change le status en PAID
 */
void Land::playerPurchase(Player* player) {
	player->pay(purchase_price);
	this->owner = player;
	this->status = LAND_STATUS::PAID;
}

/*
 * Paye la compagnie et marque le propriétaire de celle-ci comme étant le player
 * et ajoute la compagnie au propriétaire
 */
void Company::playerPurchase(Player* player) {
		Land::playerPurchase(player);
		player->acquireCompany(*this);
}

/*
 * Paye la station et marque le propriétaire de celle-ci comme étant le player
 * et ajoute la station au propriétaire
 */
void Station::playerPurchase(Player* player) {
    Land::playerPurchase(player);
    player->acquireStation(*this);
}

//TODO : les compagnie c'est en fonction du nombre que t'as fais pour tomber dessus, ici on relance des dés dcp on obtiens pas le même nombre, dcp c'est pas juste ??? (rémy)
/*
 * Renvoie le prix à payer en fonction du nombre compagnies possédées par le propriétaire
 * 1 : résultat des dés * 5
 * 2 = résultat des dés * 12
 */
int Company::getRentPrice(){
    unsigned int nbr_of_company = this->owner->getNumberOfCompanies();
    int dice_res = Dice().roll();
    switch (nbr_of_company) {
        case 1 : return dice_res*5;
        case 2 : return dice_res*12;
        default: return 0;
    }
}

/*
 * Renvoie le prix à payer en fonction du nombre de gares possédées par le propriétaire
 * 1 : 25
 * 2 : 50
 * 3 : 100
 * 4 : 200
 */
int Station::getRentPrice() {
    unsigned int nbr_of_station = this->owner->getNumberOfStations();
    switch (nbr_of_station) {
        case 1: return 25;
        case 2: return 50;
        case 3: return 100;
        case 4: return 200;
        default: return 0;
    }
}


