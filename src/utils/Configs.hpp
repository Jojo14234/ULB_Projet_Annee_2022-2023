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
	DISCONNECT,
	RANKING,
	FRIENDS,
	MESSAGE,

	NONE
};

enum class CREATE_GAME_QUERY_TYPE {
	MAX_PLAYER,
	MONEY,
	AUCTION,
	START,
	
	LEAVE,
	NONE
};

enum class RANKING_QUERY_TYPE {
	TOP,
	POSITION,
	
	LEAVE,
	NONE
};

enum class FRIENDS_QUERY_TYPE {
	SHOW,
	REQUESTS,
	ACCEPT,
	REFUSE,
	ADD,
	REMOVE,

	LEAVE,
	NONE
};


// Game
const short unsigned int MAX_NB_PLAYER = 6; 


void printMenu();
void printStart();

#endif
