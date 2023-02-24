//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_CELL_HPP
#define INFO_F209_GR5_2022_CELL_HPP
#include <json/json.h>

class Cell {
private:
    int position;
public:
    Cell(int pos): position{pos} {};
    void action(Player* player);
};

//-------------------------------
class PropertyCell: public Cell {
private:
    Property property;
    bool isOwner();
public: 
    PropertyCell(int pos, Property prop): Cell{pos}, property{prop} {};
    void action(Player* player)=0;
};

//-------------------------------
class TaxCell: public Cell{
private:
    int tax_price;
    void takeMoney();
public:
    TaxCell(int pos, int amount): Cell{pos}, tax_price{amount};
    void action(Player* player);
};

//-------------------------------
class JailCell: public Cell{
private:
    void outWithMoney();
    void outWIthCard();
    void outWithDice();
    void out();
public:
    JailCell(int pos);
    void action(Player* player);
};

//-------------------------------
class GoJailCell: public Cell{
private:
    JailCell* jail;
    void goToJail();
public: 
    GoJailCell(int pos);
    void action(Player* player);
};

//-------------------------------
class DrawableCardCell: public{
private:
    CardDeck* deck;
    void drawACard();
public:
    DrawableCardCell(int pos, CardDeck* one_deck): Cell{pos}, deck{one_deck} {};
    void action(Player* player);
};



#endif //INFO_F209_GR5_2022_CELL_HPP
