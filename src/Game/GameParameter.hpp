#pragma once

#include "../Utils/Config/ConfigsGame.hpp"
#include <sstream>
#include <string>
#include <iostream>



struct GameParameters {
    bool isFastGame = false;
    int startMoney = STARTING_MONEY;
    int maxPlayers = MAX_PLAYER_DEFAULT;
    int maxHome = MAX_HOME;
    int maxHotel = MAX_HOTEL;
    //todo add params if needed
    int maxTimeForGame = TIMER_NORMAL;
    int maxTimePerTurn = TIMER_TURN;

    GameParameters(bool isFast, std::string str) {
        if (isFast) { this->initFastParams(str); }
        else { this->initNormalParams(str); }
    }

    void initFastParams(std::string str) {
        isFastGame = true;

        std::istringstream input{str};
        int space = 0;
        for (std::string word; std::getline(input, word, ' '); space++) {
            switch (space) {
                case 0:
                    startMoney = stringToInt(word, STARTING_MONEY_FAST);
                case 1:
                    maxPlayers = stringToInt(word, MAX_PLAYER_DEFAULT);
                    break;
                case 2:
                    maxHome = stringToInt(word, MAX_HOME_FAST);
                    break;
                case 3:
                    maxHotel = stringToInt(word, MAX_HOTEL_FAST);
                    break;
                case 4:
                    maxTimeForGame = stringToInt(word, TIMER_FAST);
                    break;
                case 5:
                    maxTimePerTurn = stringToInt(word, TIMER_TURN);
                    break;
                default :
                    break;
            }
        }
    }

    void initNormalParams(std::string str) {
        isFastGame = false;

        std::istringstream input{str};
        int space = 0;
        for (std::string word; std::getline(input, word, ' '); space++) {
            switch (space) {
                case 0:
                    startMoney = stringToInt(word, STARTING_MONEY);
                case 1:
                    maxPlayers = stringToInt(word, MAX_PLAYER_DEFAULT);
                    break;
                case 2:
                    maxHome = stringToInt(word, MAX_HOME);
                    break;
                case 3:
                    maxHotel = stringToInt(word, MAX_HOTEL);
                    break;
                case 4:
                    maxTimeForGame = stringToInt(word, TIMER_NORMAL);
                    break;
                case 5:
                    maxTimePerTurn = stringToInt(word, TIMER_TURN);
                    break;
                default :
                    break;
            }
        }
    }


    int stringToInt(std::string str, int defaultValue = -1) const {
        try {
            int i = std::stoi(str);
            return i;
        }
        catch (...) { return defaultValue; }
    }

    std::string to_string(std::string user, int gc) const {
        std::string res = "";
        res += user + ":";
        res += std::to_string(gc) + ":";
        res += std::to_string(isFastGame) + ":";
        res += std::to_string(startMoney) + ":";
        res += std::to_string(maxPlayers) + ":";
        res += std::to_string(maxHome) + ":";
        res += std::to_string(maxHotel) + ":";
        res += std::to_string(maxTimeForGame) + ":";
        res += std::to_string(maxTimePerTurn);
        return res;
    }
};


