

#include "Capitalist.hpp"
#include "../Server/ClientManager/ClientManager.hpp"
#include "../Utils/randomFunctions.hpp"
#include "../Server/Game/GameServer/GameServer.hpp"
#include <unistd.h>  
#include <thread>
#include <random>
#include <algorithm>
#include "Board/Obtainable/Cells/Land/Land.hpp"
#include <vector>

/*
void Capitalist::receiveQuery(GAME_QUERY_TYPE query, sf::Packet &packet) {
    std::string s1="", s2="";
    switch (query) {
        case GAME_QUERY_TYPE::ARG1 : packet >> s1; break;
        case GAME_QUERY_TYPE::ARG2 : packet >> s1 >> s2; break;
        //case GAME_QUERY_TYPE::LEAVE : removePlayer(); break;
        default : break;
    }
    std::cout << "in capitalist : " << (int)query << " " << s1 << " " << s2 << std::endl;
}
*/



// Refactor order

/*
 * Return a string with all the game information at the start of the game.
 * String is formatted like this :
 *      nb_player|beginner|index=username|index=username|...
 *  E.G. :  3|0|0=remy|1=hugo|2=a|
 *
 *  nb_player = number of player at the start of the game [int]
 *  beginner = index of the player who begins to play [int]
 *  indexe = indexe of the player in the Players list [int]
 *  username = name of the player [string]
 */
std::string Capitalist::getStartInfos() {
    std::string ret = "";

    std::string nb_players = std::to_string(this->players.size());
    ret += nb_players + "|";
    ret += std::to_string(this->getCurrentPlayer()->getIndex()) + "|";

    for (const auto &player : this->players) {
        std::string index =     std::to_string(player.getIndex());
        std::string username =  player.getUsername();
        ret += index + "=" + username + "|";
    }
    return ret;
}

/*
 * return a string with all the game informations in it.
 * String is formatted like this :
 *      index:username:position:money:jailCardNb:property_name;level;mortgage|
 *  E.G : O:remy:5:1500:0:cyan2;3;O|1:hugo:10:1400:2:rose1;3;0:rose2;2;1|
 *
 *  indexe = 0..n players [int]
 *  username = account username [string]
 *  position = current position [int]
 *  money = current money [int]
 *  jailCardNb = number of Go out of jail [int]
 *  property_name = name of the property/station/company [string]
 *  level = building level of a property [int]
 *  mortgage = 0 = false / 1 = true [bool]
 */
std::string Capitalist::getGameInfos2() {
    std::string ret = "";
    for ( const auto &player : this->players ) {
        std::string index =     std::to_string(player.getIndex());
        std::string username =  player.getUsername();
        std::string position =  std::to_string(player.getPosition());
        std::string money =     std::to_string(player.getMoney());
        std::string jailCard =  std::to_string(player.getAllGOOJCards().size());
        ret += index + ":" + username + ":" + position + ":" + money + ":" + jailCard;

        for (const auto property : player.getAllProperties()) {
            std::string property_name =     property->getName();
            std::string property_level =    std::to_string(property->getIntLevel());
            std::string property_mortgage = std::to_string(property->isMortgaged());
            ret += ":" + property_name + ";" + property_level + ";" + property_mortgage;
        }

        for (const auto station : player.getAllStations()) {
            std::string station_name =      station->getName();
            std::string station_level =     "0";
            std::string station_mortgage =  std::to_string(station->isMortgaged());
            ret += ":" + station_name + ";" +station_level + ";" + station_mortgage;
        }

        for (const auto company : player.getAllCompanies()) {
            std::string company_name =      company->getName();
            std::string company_level =     "0";
            std::string company_mortgage =  std::to_string(company->isMortgaged());
            ret += ":" + company_name + ";" + company_level + ";" + company_mortgage;
        }
        ret += "|";
    }
    return ret;
} // todo new
std::string Capitalist::getGameInfos() {
    std::string ret = "";
    for ( const auto &player : this->players) {
        std::string index =     std::to_string(player.getIndex());
        std::string username =  player.getUsername();
        std::string position =  std::to_string(player.getPosition());
        std::string money =     std::to_string(player.getMoney());
        std::string jailCard =  std::to_string(player.getAllGOOJCards().size());
        ret += index + ":" + username + ":" + position + ":" + money + ":" + jailCard + ":";

        for (const auto property : player.getAllProperties()) {
            std::string property_name =     property->getName();
            std::string property_level =    std::to_string(property->getIntLevel());
            std::string property_mortgage = std::to_string(property->isMortgaged());
            ret += property_name + ";" + property_level + ";" + property_mortgage + ":";
        }

        for (const auto station : player.getAllStations()) {
            std::string station_name =      station->getName();
            std::string station_level =     "0";
            std::string station_mortgage =  std::to_string(station->isMortgaged());
            ret += station_name + ";" +station_level + ";" + station_mortgage + ":";
        }

        for (const auto company : player.getAllCompanies()) {
            std::string company_name =      company->getName();
            std::string company_level =     "0";
            std::string company_mortgage =  std::to_string(company->isMortgaged());
            ret += company_name + ";" + company_level + ";" + company_mortgage + ":";
        }
        ret += "|";
    }
    return ret;
}

/*
 * Return a string formatted with all the infos but this time it is readable by a human
 */
std::string Capitalist::getBetterGameInfos() {
    std::string ret = "";
    ret += "+——————————————————CAPITALI$T————————————————+\n";
    for (const auto &player : this->players) {
        std::string username =  changeStringSize(player.getUsername(), 8);
        std::string position =  changeStringSize(player.getCurrentCell()->getName(), 7);
        std::string positionI = changeStringSize(std::to_string(player.getPosition()), 2);
        std::string money =     changeStringSize(std::to_string(player.getMoney()), 7);
        ret += "| PLAYER | POSITION | MONEY | PROPERTY | LVL |\n";
        ret += "|" + username + "|" + position + " " + positionI + "|" + money + "|                |\n";
        for (const auto property : player.getAllProperties()) {
            std::string prop = changeStringSize(property->getName(),10);
            std::string level = changeStringSize(std::to_string(property->getIntLevel()), 5);
            ret += "|                           |" + prop + "|" + level + "|\n";
        }
        for (const auto property : player.getAllCompanies()) {
            std::string prop = changeStringSize(property->getName(), 10);
            int multiInt = (player.getAllCompanies().size() == 2) ? 12 : 5;
            std::string multiString = changeStringSize(std::to_string(multiInt), 5);
            ret += "|                           |" + prop + "|" + multiString + "|\n";
        }
        for (const auto property : player.getAllStations()) {
            std::string prop = changeStringSize(property->getName(), 10);
            ret += "|                           |" + prop + "|     |\n";
        }
        ret += "+——————————————————CAPITALI$T————————————————+\n";
    }
    std::string nextTurn = changeStringSize((this->getCurrentPlayer()->getUsername() + "]"), 10);
    ret += "|              A [" + nextTurn + " de jouer !      |\n";
    ret += "+————————————————————————————————————————————+\n";
    return ret;
}



/*
 * Add a player to Players list
 * If it's the first player to be added he is automatically the admin of the game
 */
void Capitalist::addPlayer(ClientManager &client) {
    Cell* starting_cell = this->board[0];
    Player player{&client, starting_cell, this->params.startMoney};
    if ( players.empty() ) { player.setAdmin(); }

    players.push_back(player);
}

/*
 * Remove a player from the Players list by matching his client address
 */
void Capitalist::removePlayer(ClientManager &client) {
    unsigned int i = 0;
    while (i < this->players.size()-1) {
        Player player = this->players[i];
        if (player.getClient() == &client) {
            this->players[i] = this->players[i+1];
            this->players[i+1] = player;
        }
        i++;
    }
    this->players.pop_back();
}

/*
 * Return the address of Players vector
 */
std::vector<Player>* Capitalist::getPlayers(){
    return &this->players;
}

std::vector<Player *> Capitalist::getPlayersAsPointers() {
    std::vector<Player*> player_pointers;
    for (auto &player : this->players){
        player_pointers.push_back(&player);
    }
    return player_pointers;
}
/*
 * Return the address of the player by matching the address of the clientManager
 * If don't find the client return nullptr
 */
Player* Capitalist::getPlayer(ClientManager &client) {
    for ( auto &player : this->players ) {
        if ( player.getClient() == &client ) { return &player; }
    }
    return nullptr;
}

/*
 * Return the player at the index "current_player_index";
 */
Player* Capitalist::getCurrentPlayer() {
    return &this->players[this->current_player_index];
}

/*
 * return the number of player in the game
 */
int Capitalist::getPlayersSize() {
    return this->players.size();
}



/*
 * Return the board
 */
Board& Capitalist::getBoard() {
    return this->board;
}

/*
 * Return the address of a land cell by it's name
 */
LandCell *Capitalist::getLandCell(std::string &name) {
    return this->board.getLandCell(name);
}



/*
 * Roll the dice and return the result
 */
int Capitalist::rollDice() {
    return this->dice.roll();
}

/*
 * Return if the last roll was a double or not
 */
bool Capitalist::rolledADouble() const {
    return this->dice.isDouble();
}

/*
 * Return the dice
 */
Dice& Capitalist::getDice() {
    return this->dice;
}


/*
 * Allow to set the exchange status
 */
void Capitalist::setExchangeStatus(ExchangeStatus status) {
    this->exchange_in_progress = status;
}

/*
 * Return the exchange status
 */
ExchangeStatus Capitalist::getExchangeStatus() const {
    return this->exchange_in_progress;
}


//Other function
/*
 * Start the game
 * Shufle the player vector
 * Set the attribut running to [TRUE]
 * Allow the first Player to play by setting to [TRUE] his attribut currently playing.
 */
void Capitalist::startGame() {
    this->setNumberOfPlayers(getPlayersSize());
    this->shufflePlayers();
    this->players[this->current_player_index].setCurrentlyPlaying(true);
    this->running = true;
}

/*
 * Return if the game is started or not
 */
bool Capitalist::isRunning() const {
    return this->running;
}

/*
 * End the current turn for the player who was playing by setting his attribut "currently playing" to [false]
 * Update the current_index
 * Begin the turn for the player with the new current index by setting his attribut "currently playing" to [true]
 */
void Capitalist::endCurrentTurn() {
    this->players[this->current_player_index].setCurrentlyPlaying(false);
    this->players[this->current_player_index].setRolled(false);

    this->current_player_index = (this->current_player_index + 1) % this->players.size();

    this->players[this->current_player_index].setCurrentlyPlaying(true);
    this->players[this->current_player_index].setRolled(false);
}


////////////////////////////////////////////
ClientManager *Capitalist::getWinner(bool is_finished) {
    if ( is_finished ){
        return calculateGameWinner();
    }

    if ( isFastGame() ){
        if ( (getNumberOfPlayersAtStart() - getPlayersSize()) == 2 ) {
            return calculateGameWinner();
        }
    }

    if (this->players.size() > 1) { return nullptr; }

    return this->players[0].getClient();


}

ClientManager *Capitalist::calculateGameWinner() {
    ClientManager* winner;
    int current_winning_patrimoine = 0;
    if (getPlayersSize() == 1){
        return players.at(0).getClient();
    }
    for (auto player : *getPlayers()){
        int patrimoine = player.getPatrimoine(isFastGame());
        if ( patrimoine > current_winning_patrimoine ){
            winner = player.getClient();
            current_winning_patrimoine = patrimoine;
        }
    }
    return winner;
}

bool Capitalist::processJailPay(Player *player) {
    if (player->getMoney() > 50) {
        if ( player->pay(50) ) { player->setStatus(PLAYER_STATUS::FREE); }
        return true;
    }
    return false;
}

bool Capitalist::processJailUseCard(Player *player) {
    if ( player->getAllGOOJCards().size() > 0 ) {
        JailCard* card = player->getAllGOOJCards().back();
        card->use();
        if (this->board.getLuckyDeck()->isJailCardInside()) {
            this->board.getLuckyDeck()->replaceJailCard();
        }
        else if (this->board.getCommunityDeck()->isJailCardInside()) {
            this->board.getCommunityDeck()->replaceJailCard();
        }
        return true;
    }
    return false;
}

bool Capitalist::processJailRoll(Player *player) {
    int roll_result = player->processRollDice(this->dice);
    player->addRollInPrison();
    if ( this->rolledADouble() ) {
        this->dice.resetDoubleCounter();
        player->setStatus(PLAYER_STATUS::FREE);
        player->processMove(roll_result, this->getBoard());
        player->getCurrentCell()->action(player);
        player->resetRollInPrison();
        return true;
    }
    else if ( player->getRollsInPrison() == 3 ) {
        this->dice.resetDoubleCounter();
        player->pay(50, true);
        if (player->getStatus() == PLAYER_STATUS::JAILED) { player->setStatus(PLAYER_STATUS::FREE); }
        player->processMove(roll_result, this->getBoard());
        player->getCurrentCell()->action(player);
        player->resetRollInPrison();
    }
    return true;
}

bool Capitalist::processBuild(Player *player, std::string &name) {
    LandCell* land = getLandCell(name);
    // Le nom ne correspond à rien
    if (!land) {return false;}
    Property* prop = dynamic_cast<Property*>(land->getLand());
    // Pas un color property
    if (!prop) { return false; }
    // Pass assez d'hotel disponible
    if (prop->getLevel() == PROPERTY_LEVEL::FOUR && (this->board.getRemainingHotel() <= 0 && !this->isFastGame())) { return false; }
    // Pas assez de maison disponible
    else if (prop->getIntLevel() < 4 && (this->board.getRemainingHome() <= 0 && !this->isFastGame())) { return false; }
    // Construction à échouer
    if (!prop->build(player, isFastGame())) { return false; }
    // On retire un hotel mais on rajoute 4 maison
    if (prop->getLevel() == PROPERTY_LEVEL::HOTEL) { this->board.getRemainingHotel()--; this->board.getRemainingHotel()+= 4; }
    // On retire une maison
    else { this->board.getRemainingHome()--; }
    return true;
}

bool Capitalist::processSellBuild(Player *player, std::string &name) {
    LandCell* land = getLandCell(name);
    // Le nom ne correspond à rien
    if (!land) {return false;}
    Property* prop = dynamic_cast<Property*>(land->getLand());
    // Si ce n'est pas une propriété de couleur
    if (!prop) {return false;}
    // Si il ne reste pas 4 maison pour remplacer un hotel
    if (prop->getLevel() == PROPERTY_LEVEL::HOTEL && this->board.getRemainingHome() < 4) { return false; }
    // Si la vente a échoué
    if (!prop->sellBuilding(player)) { return false; }
    // On rajoute 1 hotel mais on retire 4 maison
    if (prop->getLevel() == PROPERTY_LEVEL::FOUR) { this->board.getRemainingHotel()++; this->board.getRemainingHome() -= 4; }
    // On rajoute une maison
    else { this->board.getRemainingHome()++; }
    return true;
}

bool Capitalist::processMortgage(Player *player, std::string &name, bool is_fast_game) {
    LandCell* land = getLandCell(name);
    if (!land or land->getLand()->isMortgaged() ) { return false; }
    if (!(land->getOwner() == player)) { return false; }
    Property* prop = dynamic_cast<Property*>(land->getLand());
    if (!prop || prop->getLevel() == PROPERTY_LEVEL::EMPTY ) { land->getLand()->mortgage(player, is_fast_game); return true; }
    return false;
}

bool Capitalist::processLiftMortgage(Player *player, std::string &name, bool is_fast_game) {
    LandCell* land = getLandCell(name);
    if (!land or !land->getLand()->isMortgaged() ) { return false; }
    if (!(land->getOwner() == player)) { return false; }

    if ( player->getBankAccount()->getMoney() < land->getLand()->getPurchasePrice()/2 ) { return false; }
    else if (is_fast_game && player->getBankAccount()->getMoney() < land->getLand()->getPurchasePrice() * 80 / 100) { return false; }
    land->getLand()->liftMortgage(player, is_fast_game);
    return true;
}

ExchangeResult Capitalist::processSendExchangeRequest(Player *player, std::string &name, int money) {
    LandCell* land = getLandCell(name);
    if (!land ) { return ExchangeResult::NON_CHOICE; }
    if ( player->getBankAccount()->getMoney() < money ) { return ExchangeResult::NON_CHOICE; }
    Property* prop = dynamic_cast<Property*>(land->getLand());
    if (prop && prop->getLevel() != PROPERTY_LEVEL::EMPTY) { return ExchangeResult::NON_CHOICE; }

    Player* trader = land->getLand()->getOwner();
    trader->setStatus(PLAYER_STATUS::IN_EXCHANGE);
    // while true ?
    player->getClient()->sendQueryMsg(land->getLand()->getName() + ":" + std::to_string(money) + ":" + trader->getUsername(), QUERY::CONFIRM_EXCHANGE_ASKING);
    trader->getClient()->sendQueryMsg(land->getLand()->getName() + ":" + std::to_string(money) + ":" + player->getUsername(), QUERY::ASK_EXCHANGE);

    GAME_QUERY_TYPE query;
    trader->getClient()->receive(query);

    if ( query == GAME_QUERY_TYPE::ACCEPT ) {
        land->getLand()->exchange(player, money);
        trader->setStatus(PLAYER_STATUS::FREE);
        return ExchangeResult::ACCEPTED;
    } else if ( query == GAME_QUERY_TYPE::REFUSE ) {
        trader->setStatus(PLAYER_STATUS::FREE);
        return ExchangeResult::REFUSED;
    }
    return ExchangeResult::NON_CHOICE;
}

std::vector<Player*> Capitalist::startAuction(Player *player) {
    // ON INSCRIT LES JOUEURS
    std::vector<Player*> participants;
    for (auto &other : this->players ) {
        if ( &other != player ) {
            participants.push_back(&other);
            other.setStatus(PLAYER_STATUS::WAITING_FOR_AUCTION_TURN);
        }
    }
    return participants;
}

void Capitalist::shufflePlayers() {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    std::shuffle(std::begin(this->players), std::end(this->players), rd);
}


bool Capitalist::checkBankrupt(Player *player) {
    return player->getDebt() > player->getPatrimoine(isFastGame());
}

void Capitalist::processBankruptByPlayer(Player *player, Player *other) {
    for ( auto property : player->getAllProperties() ) { property->exchange(other, 0); }
    for ( auto station : player->getAllStations() ) { station->exchange(other, 0); }
    for ( auto company : player->getAllCompanies() ) { company->exchange(other, 0); }
    /*TODO : donner les cartes sortie de prison*/
    other->receive(player->getMoney());
    player->pay(player->getMoney(), true);
}

void Capitalist::setRunning(bool new_running) {
    this->running = new_running;
}

void Capitalist::setFastGame(bool is_fast) {
    fast = is_fast;
}

bool Capitalist::isFastGame() {
    return fast;
}

void Capitalist::setNumberOfPlayers(int nbr) {
    number_of_players_at_start = nbr;
}

int Capitalist::getNumberOfPlayersAtStart() {
    return number_of_players_at_start;
}

void Capitalist::forceAcquisition(Player *player) {
    int land_index_1;
    int land_index_2 = -1;

    std::vector<Land*> available_land = getBoard().getAllAvailableLand();
    int size = available_land.size();

    if (size >= 2){
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, size - 1);

        land_index_1 = distrib(gen);
        while (land_index_2 == -1 or land_index_1 == land_index_2){
            land_index_2 = distrib(gen);
        }
        player->pay(available_land.at(land_index_1)->getPurchasePrice(), true);
        player->acquireLand(available_land.at(land_index_1));
        player->pay(available_land.at(land_index_2)->getPurchasePrice(), true);
        player->acquireLand(available_land.at(land_index_2));
    }
}

int Capitalist::getStartMoney() { return params.startMoney; }

int Capitalist::getMaxPlayers() { return params.maxPlayers; }

int Capitalist::getMaxHome() { return params.maxHome; }

int Capitalist::getMaxHotels() { return params.maxHotel; }

int Capitalist::getMaxTimePerTurn() { return params.maxTimePerTurn; }

