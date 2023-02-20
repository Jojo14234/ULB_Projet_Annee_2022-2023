#include <array>


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
public:
	void action();
}


class CardCell{
public: 
	void action();
}


class CardMoney{
public: 
	void action();
}


class JailCard{
public: 
	void action();
}