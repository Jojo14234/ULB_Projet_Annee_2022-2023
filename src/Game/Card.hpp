#include <array>
#include <string>
#include <memory>


class CardDeck{
//lucky 	std::array<int, 16> money_card_nO = {1,2,3,4,5,6,7,8};	std::array<int, 16> cell_card_nO = {21,22,23,24,25,26};
// et community 
//seront des instances avec une liste de n0 carte diff
// + ajouter carte prison
protected:
	std::array<std::shared_ptr<Card>, 16> card_list;
public:
	CardDeck(std::string deck_name);
};


//###################################################
class Card{
protected:
	std:string description;
public:
	Card(Json::Value &info);
	void action(Player player);
};

//-------------------------------
class CardCell: public Card {
private:
	int dest;
	bool gain_money;
public: 
	CardCell(Json::Value &info_cell_card)
	void action(Player player);
};

//-------------------------------
class CardMoney: public Card{
private:
	int amount;
	int amount_house;
	int amount_hotel;
	
public: 
	CardMoney(Json::Value &info)
	void action(Player player);
};

//-------------------------------
class JailCard: public Card{
public: 
	void action(Player player);
};