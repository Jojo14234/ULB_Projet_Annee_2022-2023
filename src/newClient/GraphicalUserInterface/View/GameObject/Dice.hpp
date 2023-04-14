#ifndef _DICE_HPP
#define _DICE_BOX_HPP


#include "../Objects/Image.hpp"
#include "../AssetsPath.hpp"
class Dice{
    Image dice1{ObjectInfo<>(100,100,650,450),DICED};
    Image dice2{ObjectInfo<>(100,100,750,450),DICEE};

    std::string choicePath(int d){
        if(d== 1){return DICE1;}
        else if(d== 2){return DICE2;}
        else if(d== 3){return DICE3;}
        else if(d== 4){return DICE4;}
        else if(d== 5){return DICE5;}
        else if(d== 6){return DICE6;}}
    public:
        Dice(){}
        void draw(sf::RenderWindow &window) const{
            dice1.draw(window);
            dice2.draw(window);
        }

        void setDice(int d1, int d2){
            dice1.setTexture(choicePath(d1));
            dice2.setTexture(choicePath(d2));
        }

        void setHidden(){
            dice1.setHidden();
            dice2.setHidden();
        }

        void setVisible(){
            dice1.setVisible();
            dice2.setVisible();
        }
        
    

};


#endif
