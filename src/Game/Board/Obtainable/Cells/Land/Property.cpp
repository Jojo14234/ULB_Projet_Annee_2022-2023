#include "../../../../Player/Player.hpp"
#include "Property.hpp"
#include "../../../../../Server/ClientManager/ClientManager.hpp"


// Getter

/*
 * Renvoie le cout de location de la propriété en fonction du nombre de bâtiments
 * S'il n'y a pas de bâtiment et que le propriétaire possède toutes les propriétés
 * de la même couleur le loyer est doublé.
 */
int Property::getRentPrice() {
    int price = this->rent_prices[static_cast<int>(this->level)];
    return (this->getIntLevel() == 0 && hasAllSameColorProperties(this->owner)) ? price * 2 : price;
}

int Property::getIntLevel() const {
    return (int)this->level;
}

int Property::getConstructPrice() const {
    return this->construct_price;
}

PROPERTY_LEVEL Property::getLevel() const {
    return this->level;
}

PROPERTY_COLOR Property::getColor() const {
    return this->color;
}

// Setter

// Check
bool Property::isBuildable(Player *player) {
    if ( this->owner != player )                              { return false; }
    if ( this->isMortgaged() )                                { return false; }
    if ( this->getLevel() == PROPERTY_LEVEL::HOTEL )          { return false; }
    if ( !this->hasAllSameColorProperties(player) )           { return false;}
    if ( !this->AllSameColorPropertiesHaveGoodLevel(player, false) ) { return false; }
    if ( player->getBankAccount()->getMoney() < this->construct_price )  { return false; }
    return true;
}

bool Property::canSellBuilding(Player* player) {
    if ( this->owner != player ) { return false; }
    if ( this->getLevel() == PROPERTY_LEVEL::EMPTY ) {  return false; }
    if ( !this->AllSameColorPropertiesHaveGoodLevel(player, true) ) { return false;}
    return true;
}

bool Property::isMortgageable(Player* player) const {
    if ( this->owner != player ) return false; 
    if ( this->isMortgaged() ) return false; 
    if ( this->getLevel() != PROPERTY_LEVEL::EMPTY ) return false; 
    if ( ! this->AllSameColorPropertiesHaveNoBuilding(player)) return false;
    return true;
}
/*
 * Renvoie true si le player possède toutes les cartes de la même couleur que cette carte-ci.
 * Ci cette carte est une carte brune ou bleu foncé, il ne faut qu'une seule autre carte
 * Sinon il en faut 2 autres.
 */
bool Property::hasAllSameColorProperties(Player* player) {
    std::vector<Property*> same_color_properties = getOtherSameColorPropFromPlayer(player);
    if (this->getColor() == PROPERTY_COLOR::BROWN or this->color == PROPERTY_COLOR::DARK_BLUE) {return same_color_properties.size() == 1;}
    else {return same_color_properties.size() == 2;}
}

bool Property::AllSameColorPropertiesHaveNoBuilding(Player* player) const {
    for (auto property : getOtherSameColorPropFromPlayer(player)) {
        if (property->getLevel() != PROPERTY_LEVEL::EMPTY) return false;
    }
    return true;
}

// Operation

/*
 * Le joueur achète une propriété
 * modifie la liste des propriétés possédées par le joueur
 * Ajoute le joueur comme owner pour cette propriété
 */
bool Property::playerPurchase(Player* player) {
    if ( !Land::playerPurchase(player) ) { return false; };
    player->acquireProperty(*this);
    return true;
}
/*
 * Vérifie les conditions avant de permettre la construction d'un bâtiment sur une propriété
 * cond 1 : être proprio
 * cond 2 : ne pas deja avoir un hotel dessus
 * cond 3 : avoir toutes les cartes de cette couleur
 * cond 4 : 2cart de level inférieur à 2
 * cond 5 : avoir les moyens de se payer un bâtiment
 * return true si construction réussie
 */
bool Property::build(Player *player, bool is_fast_game = false) {
    // Tous les tests sont bons -> on peut construire
    if ( !this->isBuildable(player, is_fast_game) ) { return false; }
    player->pay(this->construct_price, true);
    this->levelUp();
    player->getClient()->send("Vous avez construit un bâtiment sur " + this->getName() + " son niveau est désormais [" + std::to_string(this->getIntLevel()) + "]");
    return true;
}

bool Property::isBuildable(Player *player, bool is_fast_game) {
    if ( this->owner != player )                              { /*player->getClient()->send("Vous n'êtes pas propriétaire de cette propriété (construction refusée)");*/ return false; }
    if ( this->isMortgaged() )                                { return false; }
    if ( this->getLevel() == PROPERTY_LEVEL::HOTEL )          { /*player->getClient()->send("Le niveau max de construction est atteint (construction refusée)");*/ return false; }
    if ( !is_fast_game && !this->hasAllSameColorProperties(player) )           { /*player->getClient()->send("Vous ne possédez pas toutes les propriété de la même couleur (construction refusée)");*/ return false;}
    if ( !is_fast_game && !this->AllSameColorPropertiesHaveGoodLevel(player, false) ) { /*player->getClient()->send("L'écart de niveau entre vos propriété de la même couleur est trop grand (construction refusée)");*/ return false; }
    if ( player->getBankAccount()->getMoney() < this->construct_price ) { /*player->getClient()->send("Vous êtes trop pauvre que pour construire un bâtiment sur cette propriété(construction refusée)");*/ return false; }
    if ( is_fast_game ) {
        switch (player->getBuildLevel()) {
            case 0: if ( this->getLevel() == PROPERTY_LEVEL::TWO ) { return false; }
            case 1: if ( this->getLevel() == PROPERTY_LEVEL::FOUR ) { return false; }
        }
    }
    return true;
}


/*
 * Return un vecteur contenant les autres propriétés de la même couleur que cette propriété
 * NE CONTIENT PAS LA PROPRIÉTÉ INITIALE
 */
std::vector<Property*> Property::getOtherSameColorPropFromPlayer(Player* player) const {
    std::vector<Property*> same_color_properties;
    for (auto property : player->getAllProperties()) {
        if (property->getName() != this->getName() && property->getColor() == this->getColor()) {same_color_properties.push_back(property);}
    }
    return same_color_properties;
}

/*
 * Renvoie false si l'écart de niveau entre cette propriété
 * et les autres que possède le joueur est supérieur à 1.
 */
bool Property::AllSameColorPropertiesHaveGoodLevel(Player* player, bool sell) {
    int add_to_level = (sell) ? (-1) : 1 ;
    for (auto property : getOtherSameColorPropFromPlayer(player)) {
        int calcLvl = this->getIntLevel() + add_to_level - property->getIntLevel();
        if ( calcLvl > 1 || calcLvl < -1) { return false; }
    }
    return true;
}

/*
 * Vérifie les conditions avant de permettre la vente d'un bâtiment sur une propriété
 * cond 1 : être proprio
 * cond 2 : avoir un bâtiment dessus
 * cond 4 : écart de level inférieur à 2
 * return true si vente a réussi
 */
bool Property::sellBuilding(Player *player) {
    if ( !this->canSellBuilding(player)) { return false; }
    player->receive(this->construct_price/2);
    this->levelDown();
    player->getClient()->send("Vous avez vendu un bâtiment de votre propriété à la moitié de son prix d'achat");
    player->getClient()->send("Vos amis ne vous appel plus Bob désormais !");
    return true;
}
/*
 * Level down la propriété autrement dit, retire un bâtiment
 */
void Property::levelDown() { this->level = static_cast<PROPERTY_LEVEL>(this->getIntLevel()-1); }
/*
 * Level up la propriété autrement dit, ajoute un bâtiment
 */
void Property::levelUp() { this->level = static_cast<PROPERTY_LEVEL>(this->getIntLevel()+1); }

void Property::reset() {
    this->Land::reset();
    this->level = PROPERTY_LEVEL::EMPTY;
}