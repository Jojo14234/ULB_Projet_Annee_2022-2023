#ifndef _CAPITALIST_HPP
#define _CAPITALIST_HPP

#include <SFML/Network.hpp>

#include "../utils/Configs.hpp"

#include "Player/Player.hpp"
#include "Board/Board.hpp"
#include "../Game/Board/Obtainable/Cells/LandCell.hpp"

enum class AuctionStatus {STOP, START, OTHER};
enum class ExchangeStatus{STOP, START, OTHER};
class ClientManager;


class Capitalist {

    std::vector<Player> players;
    int current_player_index = 0;
    bool running = false;

    AuctionStatus auction_in_progress = AuctionStatus::STOP;
    ExchangeStatus exchange_in_progress = ExchangeStatus::STOP;

    Board board;
    Dice dice;

public:

	Capitalist()=default;

	void receiveQuery(GAME_QUERY_TYPE query, sf::Packet &packet);


    // Refactor order

    // All the function about game Infos
    std::string getStartInfos();
    std::string getGameInfos();
    std::string getBetterGameInfos();

    // All the function about the player
    void addPlayer(ClientManager &client);
    void removePlayer(ClientManager &client);
    std::vector<Player>* getPlayers();
    Player* getPlayer(ClientManager &client);
    Player* getCurrentPlayer();
    int getPlayersSize();

    // All the function about the board or the cell
    Board& getBoard();
    LandCell* getLandCell(std::string  &name);

    // Roll Dice
    int rollDice();
    bool rolledADouble() const;
    Dice& getDice();

    // All the function about auctions
    void startAuction();
    void stopAuction();
    void setAuctionProgress(AuctionStatus progress);
    AuctionStatus getAuctionStatus() const;
    Player* getAuctionWinner();

    // All the function about exchange
    void setExchangeStatus(ExchangeStatus status);
    ExchangeStatus getExchangeStatus() const;

    // Start the game
    void startGame();
    bool isRunning() const;
    void endCurrentTurn();


    ///////////////////////////////////////
    ClientManager* getWinner();

    void processJailPay(Player* player);
    void processJailUseCard(Player* player);
    void processJailRoll(Player* player);


};


#endif