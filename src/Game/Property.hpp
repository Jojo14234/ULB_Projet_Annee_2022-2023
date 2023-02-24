//
// Created by Joachim on 14/02/2023.
//

#ifndef INFO_F209_GR5_2022_PROPERTY_HPP
#define INFO_F209_GR5_2022_PROPERTY_HPP

enum class COLOR{BROWN=1, LIGHT_BLUE=2, PINK=3, ORANGE=4, RED=5, YELLOW=6, GREEN=7, DARK_BLUE=8};
enum class CELL_STATUS{PAID, FREE, HYPOTEK};
enum class PROPERTY_LEVEL{EMPTY=0, ONE=1, TWO=2, THREE=3, FOUR=4, HOTEL=5};

class Property {
private: 
    COLOR color;
    std::string name;
    int purchase_price;
    array<int, 6> rent_prices;
    int actual_rent_price;
    int construct_price;
    CELL_STATUS status;
    PROPERTY_LEVEL level;
    Player* owner;

    void purchase();
    void rent();
    void setLevel();

public:
    Property(Json:Value prop_info);
    void action(Player* player);

};


#endif //INFO_F209_GR5_2022_PROPERTY_HPP
