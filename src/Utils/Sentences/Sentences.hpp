#pragma once

#include <string>
#include <iostream>
#include "../../Game/GameParameter.hpp"


using std::string;
using std::cout;
using std::endl;

class ServerSentence {
public:
    static void ReadException(string what) {
        cout << "[SERVER] > {Exception_read} > " << what << endl;
    }

    static void WriteException(string what) {
        cout << "[SERVER] > {Exception_write} > " << what << endl;
    }

    static void DisconnectNormal() {
        cout << "[SERVER] > Client disconnect the normal way." << endl;
    }

    static void UnknownQueryType() {
        cout << "[SERVER] > Unknown query type." << endl;
    }

    static void DisconnectAccount(string username, bool quit) {
        if (quit)   { cout << "[SERVER] > {QUIT} > "<< username <<" quit the app." << endl; }
        else        { cout << "[SERVER] > {DISCONNECT} > " << username << " disconnected from account." << endl; }
    }

    static void RegisterAccount(string username, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {REGISTER} > "<< username << success << " register." << endl;
    }

    static void LoginAccount(string username, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {REGISTER} > "<< username << success << " login." << endl;
    }

    static void JoinGame(string username, int gameCode, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {JOIN} > "<< username << success << " join game : " << gameCode << "." << endl;
    }

    static void CreateGame(string username, GameParameters params, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {CREATE} > "<< username << success << " create game with this params : \n";
        cout << "[fast : " << params.isFastGame;
        cout << "] [startMoney : " << params.startMoney;
        cout << "] [maxPlayer : " << params.maxPlayers;
        cout << "] [maxHome : " << params.maxHome;
        cout << "] [maxHotel: " << params.maxHotel;
        cout << "] [maxTurn: " << params.maxTurn << "]" << endl;
    }

    static void RankingPos(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {RANKING_POS} > " << username << success << " show ranking position" << endl;
    }

    static void RankingTop(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {RANKING_POS} > " << username << success << " show ranking top" << endl;
    }

    static void ResetRank(string username) {
        string success = (username == "admin") ? " successfully" : " failed to";
        cout << "[SERVER] > {RESET_RANK} > " << username << success << " reset everyone's statistiques" << endl;
    }

    static void FriendInfo(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_INFOS} > " << username << success << " collect all friends infos" << endl;
    }

    static void FriendList(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_LIST} > " << username << success << " show friend list" << endl;
    }

    static void FriendRequest(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_REQUEST} > " << username << success << " show friend request" << endl;
    }

    static void FriendAccept(string username, string from, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_ACCEPT} > " << username << success <<" accept a friend request from " << from << endl;
    }

    static void FriendRefuse(string username, string from, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_ACCEPT} > " << username << success <<" refuse a friend request from " << from << endl;
    }
};