#include <array>
#include <string>


class CardDeck{
protected:
	std::array<std::shared_ptr<Card>, 16> card_list;
public:
	

};

//-------------------------------
class LuckyCardDeck: public CardDeck {
	std::array<int, 16> money_card_nO = [1,2,3,4,5,6,7,8];
	std::array<int, 16> cell_card_nO = [21,22,23,24,25,26];
public:
	LuckyCardDeck();
};

//-------------------------------
class CommunityCardDeck: public CardDeck {
	std::array<int, 16> money_card_nO = [1,2,3,4,5,6,7,8];
	std::array<int, 16> cell_card_nO = [21,22,23,24,25,26];
public:
	CommunityCardDeck();
};



//###################################################
class Card{
protected:
	std:string description;
public:
	Card(int card_nO);
	void action(Player player);
};

//-------------------------------
class CardCell: public Card {
private:
	int dest;
	bool gain_money;
public: 
	void action(Player player);
};

//-------------------------------
class CardMoney: public Card{
private:
	int amount;
	int amount_house;
	int amount_hotel;
	
public: 
	void action(Player player);
};

//-------------------------------
class JailCard: public Card{
public: 
	void action(Player player);
};