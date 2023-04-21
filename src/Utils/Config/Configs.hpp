#ifndef _CONFIGS_HPP
#define _CONFIGS_HPP

#include <iostream>
#include <string>

#include "ConfigsServer.hpp"
#include "ConfigsDatabase.hpp"
#include "ConfigsGame.hpp"


// AuthentificationManager constante
const int username_min_length = 1;
const int username_max_length = 32;
const int password_min_length = 4;
const int password_max_length = 64;
const char banned_character[] = {'-', '+', '*', '$', '&', '@', '?', '!'}; //'§', '£'


// Queries
enum class QUERY_TYPE {
	LOGIN,
	REGISTER,

	JOIN_GAME,
	CREATE_GAME,
    CREATE_FAST_GAME,

	RANKING_TOP,
	RANKING_POS,
    RANKING_RESET,

    FRIENDS_INFO,
	FRIENDS_LIST,
	FRIENDS_REQUEST,
	FRIENDS_ACCEPT,
	FRIENDS_REFUSE,
	FRIENDS_ADD,
	FRIENDS_REMOVE,
	
	MESSAGE_SEND,
	MESSAGE_SHOW,

	DISCONNECT,
    QUIT,

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
    CARD,
    YES,
    NO,
    TIME_EXPIRED,
    USELESS_QUERY,

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





#endif