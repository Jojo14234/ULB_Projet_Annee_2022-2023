#ifndef _GAME_STATION_HPP
#define _GAME_STATION_HPP

#include "Land.hpp"

class Player;

class Station : public Land {

public:

    using Land::Land;

    virtual ~Station()=default;

    int getRentPrice() override ;

    bool playerPurchase(Player* player) override ;

};

#endif