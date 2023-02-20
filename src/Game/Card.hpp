#include <array>
#include <string>


class CardDeck{
protected:
	std::array<std::shared_ptr<Card>, 16> card_list;
public:


}

class CommunityCardDeck: public CardDeck {
public:
	CommunityCardDeck();
}

class LuckyCardDeck: public CardDeck {
public:
	LuckyCardDeck();
}


//-----------------------------------------------
class Card{
protected:
	std:string description;
public:
	void action();
}


class CardCell: public Card {
private:
	int dest;
	bool gain_money;
public: 
	void action();
}


class CardMoney: public Card{
private:
	int amount;
	int amount_house;
	int amount_hotel;
	
public: 
	void action();
}


class JailCard: public Card{
public: 
	void action();
}