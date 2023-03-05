#include "../../../../Player.hpp"
#include "Land.hpp"
#include "Property.hpp"
#include "Company.hpp"
#include "Station.hpp"

void Land::mortgage(Player* player){
	this->status = LAND_STATUS::HYPOTEK;
    player->receive(purchase_price/2, "hypothèque");
}

void Land::liftMortgage(Player *player) {
    if (player->pay(purchase_price/2)){
        this->status = LAND_STATUS::PAID;
    }
}

virtual void Land::playerPurchase(Player* player) {
	player->pay(purchase_price);
	this->owner = player;
	this->status = PAID;
}





void Company::playerPurchase(Player* player) {
		Land::playerPurchase(player);
		player->acquireCompany(this);
	}

int Company::getRentPrice(){
		unsigned int nbr_of_company = this->owner->getNumberOfCompanies();
		int dice_res = Dice().roll();
		switch (nbr_of_company) {
			case 1:
				return dice_res*5;
			case 2:
				return dice_res*12;

		}
	}
	//dé  jeter les dés x5 ou x12 selon le owner possession

void Station::playerPurchase(Player* player) {
		Land::playerPurchase(player);
		player->acquireStation(this);
	}

int Station::getRentPrice() {
		unsigned int nbr_of_station = this->owner->getNumberOfStations();
		switch (nbr_of_station) {
			case 1:
				return 25;
			case 2:
				return 50;
			case 3:
				return 100;
			case 4:
				return 200;
		}
	}
	// dépend de owner et le nombre de gare qu'il a