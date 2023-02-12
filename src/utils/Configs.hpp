#ifndef _CONFIGS_HPP
#define _CONFIGS_HPP

#include <iostream>
#include <string>


// Server
const auto IP = "127.0.0.1";
const auto PORT = 8080;



// Queries
enum class QUERY_TYPE {
	LOGIN = 0,
	REGISTER,
	JOIN_GAME,
	CREATE_GAME,
	DISCONNECT,
	RANKING,
	FRIENDS,
	MESSAGE,

	NONE
};

void printMenu();
void printStart();

#endif