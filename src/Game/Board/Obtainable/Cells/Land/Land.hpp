ƒ#ifndef _GAME_LAND_HPP
#define _GAME_LAND_HPP

#include <string>
#include <iostream>

enum class LAND_STATUS {PAID, FREE, HYPOTEK};

class Player;


class Land {

protected:

    Player* owner = nullptr;
	std::string name;
	int purchase_price;
    int pos;
	LAND_STATUS status = LAND_STATUS::FREE;

public: 

    Land(std::string name, int purchase_price, int pos): name{name}, purchase_price{purchase_price}, pos{pos} {};


    // Getter
	Player* getOwner() const;
    std::string getName() const;
    LAND_STATUS getStatus() const;
    int getPurchasePrice() const;
    int getPosition() const;

    // Setter
    void setOwner(Player* player);
	void setStatus(LAND_STATUS new_status);

    // Check
    bool isMortgaged() const;


    // Opération
    void mortgage(Player* player);
    void liftMortgage(Player* player);
	void mortgage(Player* player, bool is_fast_game);
    void liftMortgage(Player* player, bool is_fast_game);
    void exchange(Player* new_owner, int money);
    void reset();
    int virtual getRentPrice()=0;

    // Purchase
	virtual bool playerPurchase(Player* player);
};

#endif
