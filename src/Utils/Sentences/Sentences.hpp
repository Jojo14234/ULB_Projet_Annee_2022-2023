#pragma once

#include <string>
#include <iostream>
#include "../../Game/GameParameter.hpp"


using std::string;
using std::cout;
using std::endl;

namespace ServerSentence {
    void ReadException(string what) {
        cout << "[SERVER] > {Exception_read} > " << what << endl;
    }

    void WriteException(string what) {
        cout << "[SERVER] > {Exception_write} > " << what << endl;
    }

    void DisconnectNormal() {
        cout << "[SERVER] > Client disconnect the normal way." << endl;
    }

    void UnknownQueryType() {
        cout << "[SERVER] > Unknown query type." << endl;
    }

    void DisconnectAccount(string username, bool quit) {
        if (quit)   { cout << "[SERVER] > {QUIT} > "<< username <<" quit the app." << endl; }
        else        { cout << "[SERVER] > {DISCONNECT} > " << username << " disconnected from account." << endl; }
    }

    void RegisterAccount(string username, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {REGISTER} > "<< username << success << " register." << endl;
    }

    void LoginAccount(string username, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {REGISTER} > "<< username << success << " login." << endl;
    }

    void JoinGame(string username, int gameCode, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {JOIN} > "<< username << success << " join game : " << gameCode << "." << endl;
    }

    void CreateGame(string username, GameParameters params, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {CREATE} > "<< username << success << " create game with this params : \n";
        cout << "[fast : " << params.isFastGame;
        cout << "] [startMoney : " << params.startMoney;
        cout << "] [maxPlayer : " << params.maxPlayers;
        cout << "] [maxHome : " << params.maxHome;
        cout << "] [maxHotel: " << params.maxHotel;
        cout << "] [maxTurn: " << params.maxTurn << "]" << endl;
    }

    void RankingPos(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {RANKING_POS} > " << username << success << " show ranking position" << endl;
    }

    void RankingTop(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {RANKING_POS} > " << username << success << " show ranking top" << endl;
    }

    void ResetRank(string username) {
        string success = (username == "admin") ? " successfully" : " failed to";
        cout << "[SERVER] > {RESET_RANK} > " << username << success << " reset everyone's statistiques" << endl;
    }

    void FriendInfo(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_INFOS} > " << username << success << " collect all friends infos" << endl;
    }

    void FriendList(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_LIST} > " << username << success << " show friend list" << endl;
    }

    void FriendRequest(string username, bool successFull = true) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_REQUEST} > " << username << success << " show friend request" << endl;
    }

    void FriendAccept(string username, string from, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_ACCEPT} > " << username << success <<" accept a friend request from " << from << endl;
    }

    void FriendRefuse(string username, string from, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_ACCEPT} > " << username << success <<" refuse a friend request from " << from << endl;
    }

    void FriendAdd(string username, string who, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_ADD} > " << username << success <<" sent a friend request to " << who << endl;
    }

    void FriendRemove(string username, string who, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {FRIENDS_REMOVE} > " << username << success <<" remove " << who <<" from his/her friends." << endl;
    }

    void ShowConv(string username, string who, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {MSG_SHOW} > " << username << success <<" show its conversation with " << who << endl;
    }

    void SendMessage(string username, string who, bool successFull) {
        string success = (successFull) ? " successfully" : " failed to";
        cout << "[SERVER] > {MSG_SEND} > " << username << success <<" sent a message to " << who << endl;
    }
}