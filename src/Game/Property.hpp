//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_PROPERTY_HPP
#define INFO_F209_GR5_2022_PROPERTY_HPP

enum COLOR{BROWN, LIGHT_BLUE, PINK, ORANGE, RED, YELLOW, GREEN, DARK_BLUE};
enum CELL_STATUS{PAID, FREE, HYPOTEK};
enum PROPERTY_LEVEL{EMPTY, ONE, TWO, THREE, FOUR, HOTEL};

class Property {
private: 
    COLOR color;
    int purchase_price;
    int rent_price;
    CELL_STATUS status;
    PROPERTY_LEVEL level;
    Player* owner;

    void purchase();
    void rent();
    void setLevel();

public:
    Property();
    void action(Player* player);

};


#endif //INFO_F209_GR5_2022_PROPERTY_HPP
