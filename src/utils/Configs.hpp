#ifndef _CONFIGS_HPP
#define _CONFIGS_HPP

#include <iostream>
#include <string>


// Server
const auto IP = "127.0.0.1";
const auto PORT = 8080;

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

	RANKING_TOP,
	RANKING_POS,

	FRIENDS_SHOW,
	FRIENDS_REQUEST,
	FRIENDS_ACCEPT,
	FRIENDS_REFUSE,
	FRIENDS_ADD,
	FRIENDS_REMOVE,
	
	MESSAGE,
	DISCONNECT,

	NONE
};

enum class GAME_QUERY_TYPE {
	ROLL_DICE = 1,

	BUY,

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



// Game
const short unsigned int MAX_NB_PLAYER = 6; 


void printMenu();
void printStart();

#endif
