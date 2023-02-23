//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_CELL_HPP
#define INFO_F209_GR5_2022_CELL_HPP


class Cell {
private:
    int position;
public:
    Cell(int pos);
    void action(Player* player);
};
//-------------------------------
class PropertyCell: public Cell {
private:
    Property property;
    bool isOwner();
public: 
    PropertyCell()
    void action(Player* player)=0;
}

//-------------------------------
class TaxCell: public Cell{
private:
    int price;
    void takeMoney();
public:
    TaxCell();
    void action(Player* player);
}

//-------------------------------
class JailCell: public Cell{
private:
    void outWithMoney();
    void outWIthCard();
    void outWithDice();
    void out();
public:
    JailCell();
    void action(Player* player);
}

//-------------------------------
class GoJailCell: public Cell{
private:
    JailCell* jail;
    void goToJail();
public: 
    GoJailCell();
    void action(Player* player);
}

//-------------------------------
class DrawableCardCell: public{
private:
    CardDeck* deck;
    void drawACard();
public:
    DrawableCardCell()
    void action(Player* player);
}



#endif //INFO_F209_GR5_2022_CELL_HPP
