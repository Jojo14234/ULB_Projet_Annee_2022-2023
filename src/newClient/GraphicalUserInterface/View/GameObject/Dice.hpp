#ifndef _DICE_HPP
#define _DICE_BOX_HPP


#include "../Objects/Image.hpp"
#include "../AssetsPath.hpp"
class Dice{
    Image dice1{ObjectInfo<>(WINDOW_WIDTH/16.f,WINDOW_HEIGHT/9.f,WINDOW_WIDTH/2.46f,WINDOW_HEIGHT/2.f),DICED};
    Image dice2{ObjectInfo<>(WINDOW_WIDTH/16.f,WINDOW_HEIGHT/9.f,WINDOW_WIDTH/2.133f,WINDOW_HEIGHT/2.f),DICEE};

    std::string choicePath(int d){
        if(d== 1){return DICE1;}
        else if(d== 2){return DICE2;}
        else if(d== 3){return DICE3;}
        else if(d== 4){return DICE4;}
        else if(d== 5){return DICE5;}
        else if(d== 6){return DICE6;}
        return DICED;}
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

        void resetDice(){
            dice1.setTexture(DICED);
            dice2.setTexture(DICEE);
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
