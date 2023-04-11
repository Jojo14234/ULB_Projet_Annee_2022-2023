#include "../../../../Player/Player.hpp"
#include "Land.hpp"
#include "Property.hpp"
#include "Company.hpp"
#include "Station.hpp"

#include <cmath>

// Getter
Player *Land::getOwner()        const { return this->owner; }
std::string Land::getName()     const { return this->name; }
LAND_STATUS Land::getStatus()   const { return this->status; }
int Land::getPurchasePrice()    const { return this->purchase_price; }
int Land::getPosition()         const { return this->pos; }

// Setter
void Land::setOwner(Player *player) { this->owner = player; status = LAND_STATUS::PAID; }
void Land::setStatus(LAND_STATUS new_status) { this->status = new_status; }

// Check
bool Land::isMortgaged() const { return status == LAND_STATUS::HYPOTEK; }

bool Land::isMortgageable(Player* player) const {
    if ( this->owner != player ) return false; 
    if ( this->isMortgaged() ) return false;
    return true;
}

// Opération
/*
 * Met en hypothèque une propriété et donne la moitié du prix d'achat au player
 */
void Land::mortgage(Player* player, bool is_fast_game) {
	this->status = LAND_STATUS::HYPOTEK;

    if (is_fast_game) player->receive(purchase_price * 80 / 100, "hypothèque");

    else player->receive(purchase_price/2, "hypothèque");
}
/*
 * Le `player` rachète la propriété qui était en hypothèque et la paye moitié prix
 */
void Land::liftMortgage(Player *player, bool is_fast_game) {

    if ( !is_fast_game && player->pay(purchase_price/2) ) { this->status = LAND_STATUS::PAID; }

    else if ( is_fast_game && player->pay(purchase_price * 80 / 100) ) { this->status = LAND_STATUS::PAID; }

}
/*
 * permet l'échange d'une propriété entre 2 joueur contre de l'argent
 */
void Land::exchange(Player *new_owner, int money) {
    this->owner->removeLand(this);
    new_owner->pay(money);
    this->owner->receive(money, new_owner->getUsername());
    new_owner->acquireLand(this);
    this->setOwner(new_owner);
}
void Land::reset() {
    this->status = LAND_STATUS::FREE;
    this->owner = nullptr;
}



// Purchase
/*
 * Pay le Land et marque owner comme étant le player, change le status en PAID
 */
bool Land::playerPurchase(Player* player) {
	if ( !player->pay(purchase_price) ) { return false; };
	this->owner = player;
	this->status = LAND_STATUS::PAID;
    return true;
}

/*
 * Paye la compagnie et marque le propriétaire de celle-ci comme étant le player
 * et ajoute la compagnie au propriétaire
 */
bool Company::playerPurchase(Player* player) {
    if ( !Land::playerPurchase(player) ) {  return false; }
    player->acquireCompany(*this);
    return true;
}

/*
 * Paye la station et marque le propriétaire de celle-ci comme étant le player
 * et ajoute la station au propriétaire
 */
bool Station::playerPurchase(Player* player) {
    if ( !Land::playerPurchase(player) ) { return false; }
    player->acquireStation(*this);
    return true;
}



// Rent price
/*
 * Renvoie le prix à payer en fonction du nombre compagnies possédées par le propriétaire
 * 1 : résultat des dés * 5
 * 2 = résultat des dés * 12
 */
int Company::getRentPrice(){
    unsigned int nb_company = this->owner->getNumberOfCompanies();
    int result = this->owner->getResultLastRoll();
    if (nb_company == 1) { return result * 5; }
    else if (nb_company == 2) {return result * 12; }
    return 0;
}

/*
 * Renvoie le prix à payer en fonction du nombre de gares possédées par le propriétaire
 * 1 : 25
 * 2 : 50
 * 3 : 100
 * 4 : 200
 *
 * f(x) = 25 * 2 ^ ((x-1)/1)
 */
int Station::getRentPrice() {
    unsigned int nbr_of_station = this->owner->getNumberOfStations();
    return 25 * pow(2, (nbr_of_station-1)/1.0);
}


