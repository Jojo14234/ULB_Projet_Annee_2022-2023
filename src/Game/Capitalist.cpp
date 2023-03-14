

#include "Capitalist.hpp"
#include "../Server/ClientManager/ClientManager.hpp"




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

/*
void Capitalist::sendMessage(std::string &output) {
    output = "coucou ici capitalist";
}
*/
void Capitalist::addPlayer(ClientManager &client) {
    players.push_back(Player(&client, board.getCellByIndex(0)));
    if (players.size() == 1) {players.at(0).setAdmin(); players[0].setCurrentlyPlaying(true);}
}

void Capitalist::removePlayer() {
    //TODO : find correspinding id of player to delete
    players.pop_back();
}

void Capitalist::startGame() {
    running = true;
}

Player* Capitalist::getCurrentPlayer() {
    return &players.at(current_player_index);
}

bool Capitalist::isRunning() const {
    return running;
}

void Capitalist::endCurrentTurn() {
    players[current_player_index].setCurrentlyPlaying(false);
    players[current_player_index].setRolled(false);
    (current_player_index += 1) %= (players.size());
    players[current_player_index].setCurrentlyPlaying(true);
    players[current_player_index].getClient()->send("C'est à votre tour.");
}

int Capitalist::rollDice() {return dice.roll();}

std::string Capitalist::getRollString() {
    int roll = rollDice();
    std::string str = "Valeur des dés : [" + std::to_string(roll) + "]\n";
    if (rolledADouble()) {str += "Vous avez obtenus un double [" + std::to_string(roll/2) + "]\nIel va pourvoir rejouer !"; }
    return str;
}

bool Capitalist::rolledADouble() {
    return dice.isDouble();
}

Player* Capitalist::getPlayerByClient(ClientManager &client) {
    Player* ret = nullptr;
    for (auto &player : players){
        if (player.getClient() == &client){
            ret = &player;
            break;
        }
    }
    return ret;
}

Dice& Capitalist::getDice() {
    return dice;
}

Board* Capitalist::getBoard() {
    return &board;
}

int Capitalist::getNumberOfPlayers() {
    return players.size();
}

std::vector<Player>* Capitalist::getPlayers(){
    return &players; //ça marche ceci?
}

void Capitalist::startAuction() {
    auction_in_progress = 1;
    for (auto &player : players){
            player.leaveAuctionSilently();
    }
}

void Capitalist::stopAuction() {auction_in_progress = 0;}

Player *Capitalist::identifyAuctionWinner() {
    Player* winner = nullptr;
    for (auto player : players){
        if (player.isInAuction()){
            if (winner == nullptr){
                winner = &player;
            }
            else {
                return nullptr;
            }
        }
    }
    return winner;
}

LandCell *Capitalist::getCellByName(std::string &name) {
    return board.getCellByName(name);
}