#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>


struct RankingINFO {
    int pos;
    std::string username;
    int points;

    RankingINFO(const std::string& str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, ':'); colon_nb++) {
            switch (colon_nb) {
                case 0 : pos = atoi(word.c_str()); break;
                case 1 : username = word.c_str(); break;
                case 2 : points = atoi(word.c_str()); break;
                default : break;
            }
        }
    }
};

struct RankingInfosList {

    std::vector<RankingINFO> infos;
    
    RankingInfosList(const std::string& str) {
        std::istringstream input{str};
        int colon_nb = 0;
        for (std::string word; std::getline(input, word, '|'); colon_nb++) {
            RankingINFO info = RankingINFO{word};
            this->infos.push_back(info);
        }
    }
};



