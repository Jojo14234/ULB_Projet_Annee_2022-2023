#ifndef _GAME_COMPANY_HPP
#define _GAME_COMPANY_HPP

#include "Land.hpp"

class Player;

class Company : public Land {

public:

    using Land::Land;

    virtual ~Company()=default;

    int getRentPrice() override ;

	bool playerPurchase(Player* player) override ;

};

#endif