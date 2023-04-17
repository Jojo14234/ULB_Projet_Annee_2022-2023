//
// Created by Joachim on 14/02/2023.
//

#include "Player.hpp"
#include "BankAccount.hpp"
#include "../../Server/Game/GameServer.hpp"
//#include "../../Server/ClientManager/ClientManager.hpp"

/*
 * Renvoie le résultat du lancé de dés.
 * Lance les dés -> met à jour l'attribut "has_rolled" à [TRUE]
 * Si ce n'est pas un double, on reset le compteur de double
 * Si le compteur de double >= 3, passe le joueur en status [JAILED], reset le compteur de double, renvoie 0 comme résultat.
 * Si c'est un double mais que le compteur n'est pas encore à 3, remet la valeur "has_rolled" à [FALSE] et renvoie le résultat
 */
int Player::processRollDice(Dice &dice) {
    int result = this->roll(dice);
    // If no double then return
    if ( !dice.isDouble() ) { dice.resetDoubleCounter(); return result; }
    // if 3 double then go to jail
    if ( dice.getDoubleCounter() >= 3 ) { this->setStatus(JAILED); dice.resetDoubleCounter(); return 0; }
    // else just reset the setRolled because player will have to play again
    this->setRolled(false);
    return result;
}


// SETTER
void Player::setAdmin() { admin = true; }
void Player::setCurrentlyPlaying(bool playing) { currently_playing = playing; }
void Player::setRolled(bool rolled) {has_rolled = rolled;}
void Player::setExchangeFromJail() { exchange_from_jail = true; }
void Player::setStatus(PLAYER_STATUS new_status) {
    std::cout << "PLAYER STATUS CHANGE" << std::endl;
    std::cout << this->getUsername() << " is now " << (int)new_status << std::endl;
    std::cout << "FREE=0, JAIL=1, LOST=2, IN_EXCHANGE=3, ASK_AUCTION=4, WAITING_FOR_AUCTION_TURN=5, AUCTION_TURN=6, BANKRUPT_SUS=7, BANKRUPT_CONF=8, OTHER=9" << std::endl;
    status = new_status;
}
void Player::setPlayerToRefund(Player* player){ player_to_refund = player; }
void Player::setIndex(int new_index) {
    if (this->index == -1 ) { this->index = new_index; };
}
void Player::setExitJail() { this->status = FREE; }






// GETTER
bool Player::isAdmin() const { return admin; }
ClientManager *Player::getClient() const { return client; }
std::string Player::getUsername() const { return client->getAccount()->getUsername(); }
Cell *Player::getCurrentCell() const { return current_cell; }
int Player::getRollsInPrison() const { return rolls_in_prison; }
std::vector<Property*> Player::getAllProperties() const { return properties; }
std::vector<Company*> Player::getAllCompanies() const { return companies; }
std::vector<Station*> Player::getAllStations() const { return stations; }
std::vector<JailCard*> Player::getAllGOOJCards() const { return GOOJ_cards; }
int Player::getNumberOfStations() const { return stations.size(); }
int Player::getNumberOfCompanies() const { return companies.size(); }
PLAYER_STATUS Player::getStatus() { return status; }
BankAccount* Player::getBankAccount(){ return &bank_account; }
int Player::getPosition() const { return this->current_cell->getPosition(); }
int Player::getMoney() const { return this->bank_account.getMoney(); }
Player* Player::getPlayerToRefund() { return player_to_refund; }
int Player::getPatrimoine(bool is_fast_game) {
    float weighting;
    if (is_fast_game){
        weighting = 0.8;
    }
    else {
        weighting = 0.5;
    }
    int money = getMoney();
    for (auto property : this->properties) {
        int money_from_sell_buildings = property->getIntLevel() * (property->getConstructPrice() * weighting);
        int money_from_hypotheque = property->getPurchasePrice() * weighting;
        money += money_from_sell_buildings;
        money += money_from_hypotheque;
    }

    for (auto station : this->stations) {
        int money_from_hypotheque = station->getPurchasePrice() * weighting;
        money += money_from_hypotheque;
    }

    for (auto company : this->companies) {
        int money_from_hypotheque = company->getPurchasePrice() * weighting;
        money += money_from_hypotheque;
    }
    return money;
}
int Player::getIndex() const { return this->index; }
int Player::getDebt() const { return this->money_debt; }


// CHECK
bool Player::isItMe(ClientManager &client) const { return this->client == &client; }
bool Player::isCurrentlyPLaying() const { return currently_playing; }
bool Player::isInJail() const { return (status == JAILED); }
int Player::hasGOOJCards() const { return (GOOJ_cards.size() > 0); }
bool Player::hasRolled() const { return has_rolled; }
bool Player::isBankrupt() const { return this->money_debt > this->getMoney(); }
bool Player::isBankruptToPlayer() const { return this->player_to_refund != nullptr; }




// ABOUT Client
void Player::send(std::string &s) const { if ( client ) client->send(s); }
void Player::send(std::string &&s) const { if ( client ) client->send(s); }


// ABOUT bankAccount
bool Player::pay(int amount, bool forced) {
    // Assez d'argent -> on paye et tout va bien
    if ( bank_account.canPay(amount) ) { 
        bank_account.pay(amount);
        this->client->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_LOSE_MONEY, std::to_string(this->getIndex()) + ":" + std::to_string(amount) + ":" + std::to_string(this->getMoney()));
        return true;
    }
    // Pas assez d'argent, mais pas forcer -> on ne paye pas et on renvoie qu'on a pas payer.
    if ( !forced ) {this->getClient()->sendQueryMsg("", QUERY::INFOS_NOT_ENOUGH_MONEY); return false; }
    else {this->getClient()->sendQueryMsg("", QUERY::INFOS_DEBT); return false;}
    // Pas assez d'argent mais forcer de payer -> on passe en status de faillite suspecter mais on ne paye pas non plus.
    this->status = PLAYER_STATUS::BANKRUPT_SUSPECTED;
    this->money_debt += amount;
    return false; // TODO PTT FAUT METTRE RETURN TRUE (AVANT ON PAYAIS MÊME SI ON AVAIT PAS LES FONDS).
}
void Player::receive(int amount) {
    bank_account.gain(amount);
    this->client->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_WON_MONEY, std::to_string(this->getIndex()) + ":" + std::to_string(amount) + ":" + std::to_string(this->getMoney()));
    //getClient()->send("Vous avez reçu " + std::to_string(amount) + "e de " + source);
}
    

// MOUVEMENT
void Player::move(Cell *cell, bool pass_by_start) {
    if (passedByStart(cell, pass_by_start)) {
        this->receive(200);
        this->increaseBuildLevel();
    }
    current_cell = cell;
    this->client->getGameServer()->updateAllClientsWithQuery(QUERY::INFOS_PLAYER_MOVE, this->getUsername() + ":" + this->current_cell->getName() + ":" + std::to_string(this->getMoney()));
}
bool Player::passedByStart(Cell* cell, bool pass_by_start) {
    if (cell->getPosition() - current_cell->getPosition() <= 0 and pass_by_start) {
        return true;
    }
    return false;
}
void Player::goToJail(Cell *cell) {
    move(cell, false);
    this->status = JAILED;
    this->rolls_in_prison = 0;
    this->has_rolled = true;
}
// BOTH processMove are Use
void Player::processMove(Cell* new_cell, bool gainMoneyIfPassByStart) {
    if ( gainMoneyIfPassByStart && this->current_cell->getPosition() > new_cell->getPosition() ) {
        this->receive(MONEY_START_CELL);
        this->increaseBuildLevel();
    }
    this->current_cell = new_cell;
}
Cell* Player::processMove(int step, Board &board) {
    // Calcul of the new Cell idx
    int new_cell_idx = this->current_cell->getPosition() + step;
    // If the new idx is greater than the board size then we are on the start_cell and we receive money
    if (new_cell_idx >= BOARD_SIZE) { this->receive(MONEY_START_CELL); this->increaseBuildLevel(); }
    // set the new current_cell
    this->current_cell = board[new_cell_idx];
    return this->current_cell;
};


// roll_in_prison
void Player::addRollInPrison() { rolls_in_prison++; }
void Player::resetRollInPrison() { this->rolls_in_prison = 0; }


// OTHER
void Player::looseGOOJCard(){
    JailCard* card = GOOJ_cards.back();
    this->GOOJ_cards.pop_back();
    card->setOwner(nullptr);
    //client->send("Vous perdez votre carte prison suite à son utilisation.\n");
}
void Player::useGOOJCard() {
    this->status = PLAYER_STATUS::FREE;
    GOOJ_cards.pop_back();
}

void Player::removeOneGoOutOfJailCard(JailCard *card) {
    if (this->GOOJ_cards.size() == 0) { return; }
    unsigned int i = 0;
    while (i < this->GOOJ_cards.size()) {
        if (this->GOOJ_cards[i] == card) { this->GOOJ_cards.erase(this->GOOJ_cards.begin() + i); }
    }
}

void Player::resetDebt() {
    this->money_debt = 0;
    this->player_to_refund = nullptr;
    this->status = PLAYER_STATUS::FREE;
}



int Player::roll(Dice &dice) {
    setRolled(true);
    this->result_last_roll = dice.roll();
    return this->result_last_roll;
}

void Player::setResultLastRoll(int new_result) {
    this->result_last_roll = new_result;
}

int Player::getResultLastRoll() {
    return this->result_last_roll;
}

void Player::increaseBuildLevel() {
    if (build_level < 2){
        build_level++;
    }
}

//ne pas ajouter de méthodes pour payer dans ces méthodes, elles sont aussi utilisées pour les échanges
/*
 * check what type of land it is (used for exchanges)
 */
void Player::acquireLand(Land *land) {
    Property* p = dynamic_cast<Property*>(land);
    if (p != nullptr) { acquireProperty(*p); return;}
    Company* c = dynamic_cast<Company*>(land);
    if (c != nullptr) { acquireCompany(*c); return;}
    Station* s = dynamic_cast<Station*>(land);
    if (s != nullptr) { acquireStation(*s); return;}
}
void Player::acquireProperty(Property &prop) {
    prop.setOwner(this);
    properties.push_back(&prop);
}
void Player::acquireCompany(Company &comp) {
    comp.setOwner(this);
    companies.push_back(&comp);
}
void Player::acquireStation(Station &station) {
    station.setOwner(this);
    stations.push_back(&station);
}
void Player::acquireGOOJCard(JailCard *jail_card) {
    jail_card->setOwner(this);
    GOOJ_cards.push_back(jail_card);
}

//TODO
void Player::removeLand(Land *land){
    int index = 0;
    Property* p = dynamic_cast<Property*>(land);
    if (p != nullptr) {
        for (auto property : properties) {
            if (property == p) { properties.erase(properties.begin()+index); }
            index++;
        }
        return;
    }
    Company* c = dynamic_cast<Company*>(land);
    if (c != nullptr) {
        for (auto company : companies) {
            if (company == c) { companies.erase(companies.begin()+index); }
            index++;
        }
        return;
    }
    Station* s = dynamic_cast<Station*>(land);
    if (s != nullptr) {
        for (auto station : stations) {
            if (station == s) { stations.erase(stations.begin()+index); }
            index++;
        }
        return;
    }
}
void Player::removeProperty(Property* p) {
    for (auto property : properties) {
        if (property == p) { properties.erase(properties.begin()+index); }
        index++;
    }
}
void Player::removeStation(Station* s) {
    for (auto station : stations) {
        if (station == s) { stations.erase(stations.begin()+index); }
        index++;
    }
}
void Player::removeCompagnie(Company* c) {
    for (auto company : companies) {
        if (company == c) { companies.erase(companies.begin()+index); }
        index++;
    }
}


// STRING
std::string Player::getAllPossession(){
    std::string ret_string = "";
    for (auto property : properties ) { ret_string += property->getName() + ":"; }
    for (auto company : companies ) { ret_string += company->getName() + ":"; }
    for (auto station : stations ) { ret_string += station->getName() + ":"; }
    return ret_string;
}
std::string Player::getAllPossessionMortgageable() {
    std::string ret_string = "";
    for ( auto property : properties ) { if ( !property->isMortgaged() && property->getLevel() == PROPERTY_LEVEL::EMPTY ) { ret_string += property->getName() + ":"; } }
    for ( auto company : companies ) { if ( !company->isMortgaged() ) { ret_string += company->getName() + ":"; } }
    for ( auto station : stations ) { if ( !station->isMortgaged() ) { ret_string += station->getName() + ":"; } }
    return ret_string;
}
std::string Player::getAllPossessionLiftMortgageable() {
    std::string str = "";
    for ( auto property : properties ) { if ( property->isMortgaged() ) { str += property->getName() + ":"; } }
    for ( auto company : companies ) { if ( company->isMortgaged() ) { str += company->getName() + ":"; } }
    for ( auto station : stations ) { if ( station->isMortgaged() ) { str += station->getName() + ":"; } }
    return str;
}
std::string Player::getAllBuildableProperties(bool is_fast_game) {
    std::string str = "";
    for ( auto property : this->getAllProperties() ) { if ( property->isBuildable(this, is_fast_game) ) { str += property->getName() + ":"; } }
    return str;
}
std::string Player::getAllSellableBuildProperties() {
    std::string str = "";
    for ( auto property : getAllProperties() ) { if ( property->canSellBuilding(this) ) { str += property->getName() + ":"; } }
    return str;
}
std::string Player::getAllExchangeablePossession() {
    std::string str = "";
    for ( auto property : properties ) { if ( property->getLevel() == PROPERTY_LEVEL::EMPTY ) { str += property->getName() + ":"; } }
    for ( auto company : companies )  { str += company->getName() + ":"; }
    for ( auto station : stations )    { str += station->getName() + ":"; }
    return str;
}
/*
 * Return a string formatted with all the infos about the roll dice
 * r1 = result of the first die
 * r2 = result of the second die
 * r = Result of both die (r1 + r2)
 * d = is double ? (0 false, true 1)
 * dc = double counter;
 */
std::string Player::rollInfos(Dice &dice) {
    std::string r1 = std::to_string(dice.getDice1());
    std::string r2 = std::to_string(dice.getDice2());
    std::string r = std::to_string(dice.getResults());
    std::string d = std::to_string(dice.isDouble());
    std::string dc = std::to_string(dice.getDoubleCounter());
    return r1 + ":" + r2 + ":" + r + ":" + d + ":" + dc;
}


//BOOL

bool Player::hasBuildableProperties(){
    for ( auto property : this->getAllProperties() ) { if ( property->isBuildable(this) ) return true;}
    return false;
}
bool Player::hasSellableProperties(){
    for ( auto property : this->getAllProperties() ) { if ( property->canSellBuilding(this) ) return true;}
    return false;
}
bool Player::hasMortgageableLand(){
    for ( auto land : this->getAllLand() ) { if ( land->isMortgageable(this) ) return true;}
    return false;
}
bool Player::hasUnmortgageableLand(){
    for ( auto land : this->getAllLand() ) { if ( land->isMortgaged() ) return true;}
    return false;
}
bool Player::canExchangeLand(){
    for ( auto& player : * (this->getClient()->getGameServer()->getGame()->getPlayers())){
        if (player.getIndex() == this->getIndex()) continue;
        if (player.getAllLand().size() > 0) return true;
    }
    return false;
}


// NEW FUNCTION

std::vector<Land *> Player::getAllLand() {
    std::vector<Land*> lands;
    for ( auto property : this->properties ) { lands.push_back(property); }
    for ( auto station : this->stations ) { lands.push_back(station); }
    for ( auto company : this->companies ) { lands.push_back(company); }
    return lands;
}

int Player::getBuildLevel() {
    return build_level;
}