#pragma once

#include <string>

// Capitalist
const auto STARTING_MONEY = 1500;
const auto MAX_PLAYER_DEFAULT = 8;
const auto MONEY_START_CELL = 200;
const auto BOARD_SIZE = 40;

const int PRISON_INDEX = 10;
const int TIMER_NORMAL = 3600 * 3;
const int TIMER_TURN_NORMAL = 300;

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
const int MAX_TURN = 1000;

// Fast Game
const auto STARTING_MONEY_FAST = 3000;
const int MAX_HOTEL_FAST = 9999;
const int MAX_HOME_FAST = 9999;
const int TIMER_FAST = 3600;
