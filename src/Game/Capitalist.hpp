#ifndef _CAPITALIST_HPP
#define _CAPITALIST_HPP

#include <SFML/Network.hpp>

#include "../utils/Configs.hpp"

#include "Player/Player.hpp"
#include "Board/Board.hpp"
#include "../Game/Board/Obtainable/Cells/LandCell.hpp"

enum class AuctionStatus {STOP, START, OTHER};
enum class ExchangeStatus{STOP, START, OTHER};
enum class ExchangeResult{ACCEPTED, REFUSED, NON_CHOICE};
class ClientManager;


class Capitalist {

    std::vector<Player> players;
    int current_player_index = 0;
    bool running = false;
    bool fast = false;
    int number_of_players_at_start;

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
    std::string getGameInfos2();
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
    ClientManager* calculateGameWinner();

    void processJailPay(Player* player);
    void processJailUseCard(Player* player);
    void processJailRoll(Player* player);
    bool processBuild(Player *player, std::string &name);
    bool processSellBuild(Player *player, std::string &name);
    bool processMortgage(Player *player, std::string &name);
    bool processLiftMortgage(Player *player, std::string &name);
    ExchangeResult processSendExchangeRequest(Player *player, std::string &name, int money);
    bool processMortgage(Player *player, std::string &name, bool is_fast_game);
    bool processLiftMortgage(Player *player, std::string &name, bool is_fast_game);
    bool processSendExchangeRequest(Player *player, std::string &name, int money);
    std::vector<Player*> processAskAuction(Player *player, std::string &name);
    bool checkBankrupt(Player *player);
    void processBankruptByPlayer(Player *player, Player* other);

    void shufflePlayers();

    void setRunning(bool new_running);

    bool isFastGame();
    void setFastGame(bool is_fast);
    void setNumberOfPlayers(int nbr);
    int getNumberOfPlayersAtStart();

    void forceAcquisition(Player *player);

};


#endif