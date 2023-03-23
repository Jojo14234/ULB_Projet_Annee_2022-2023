#ifndef _CONFIGS_HPP
#define _CONFIGS_HPP

#include <iostream>
#include <string>


// Server
const auto IP = "127.0.0.1";
const auto PORT = 8080;
const auto STARTING_MONEY = 1500;
const auto MONEY_START_CELL = 200;
const auto BOARD_SIZE = 40;

const int PRISON_INDEX = 10;

// AuthentificationManager constante
const int username_min_length = 1;
const int username_max_length = 32;
const int password_min_length = 4;
const int password_max_length = 64;
const char banned_character[] = {'-', '+', '*', '$', '&', '@', '?', '!'}; //'§', '£'


// User
constexpr int MAX_FRIENDS = 20;
constexpr int MAX_REQUESTS = 20;

// Chemin Database
const std::string DB_PATH = "db.bin";

// Chemin fichier JSON
const std::string CARD_DATA = "Game/Board/Obtainable/data/card_data.json";
const std::string CELL_DATA = "Game/Board/Obtainable/data/cell_data.json";
const std::string PROPERTY_DATA = "Game/Board/Obtainable/data/property_data.json";

// CONSTANTE GAME
const int starting_bid = 10;
const int MAX_WAIT_EXCHANGE = 15;
const int MAX_WAIT_AUCTION = 15;
const int MAX_HOTEL = 12;
const int MAX_HOME = 32;




// Queries
enum class QUERY_TYPE {
	LOGIN,
	REGISTER,

	JOIN_GAME,
	CREATE_GAME,

	RANKING_TOP,
	RANKING_POS,
    RANKING_RESET,

	FRIENDS_LIST,
	FRIENDS_REQUEST,
	FRIENDS_ACCEPT,
	FRIENDS_REFUSE,
	FRIENDS_ADD,
	FRIENDS_REMOVE,
	
	MESSAGE_SEND,
	MESSAGE_SHOW,

	DISCONNECT,

	NONE
};

enum class GAME_QUERY_TYPE {
    START,
    END_TURN,
	ROLL_DICE,
    PAY,
	BUY,
    USEGOOJCARD,
    BID,
    LEAVE_BID,
    SELECT,
    MORTGAGE,
    LIFT_MORTGAGE,
    TRADE,
    LEAVE_SELECTION,
    EXCHANGE,
    BUILD,
    SELL_BUILDINGS,
    GIVE_UP,
    ACCEPT,
    REFUSE,
    DECLINE,
    PARTICIPATE,

	ARG1, // temp
	ARG2, // temp
	// add others

	LEAVE,
	NONE
};

enum class CREATE_GAME_QUERY_TYPE {
	MAX_PLAYER,
	MONEY,
	AUCTION,
	START,
	
	NONE
};

enum class PROPERTY_COLOR {
    BROWN=1,
    LIGHT_BLUE=2,
    PINK=3,
    ORANGE=4,
    RED=5,
    YELLOW=6,
    GREEN=7,
    DARK_BLUE=8
};


// Game
const short unsigned int MAX_NB_PLAYER = 6; 


#endif