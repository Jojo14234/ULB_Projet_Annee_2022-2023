#ifndef _INFO_BOX_HPP
#define _INFO_BOX_HPP

#include "../Objects/Box.hpp"
#include "../Objects/Image.hpp"
#include "../Objects/ObjectInfo.hpp"

#include <iostream>

#include "Money.hpp"

#include "../AssetsPath.hpp"
class InfoBox{
    Image suitcase;
    std::vector<std::shared_ptr<Money>> allmoney;
    ObjectInfo<> info;

    public:
        InfoBox(ObjectInfo <>info):info(info),suitcase(info,INFOBOX_PATH)
        {   }
        
        void draw(sf::RenderWindow &window) const {
            suitcase.draw(window);
            for (auto i: allmoney){
                i->draw(window);
            }}

        void initMoney( std::vector<std::string> colorlist, int start_money){
            for ( int i = 0; i < 6; i++){

                sf::Color color;

                if (colorlist[i] == "red"){color = sf::Color::Red;}
                else if (colorlist[i] == "blue"){color = sf::Color::Blue;}
                else if (colorlist[i] == "green"){ color =  sf::Color::Green;}
                else if (colorlist[i] == "magenta"){color = sf::Color::Magenta;}
                else if (colorlist[i] == "cyan"){ color =  sf::Color::Cyan;}
                else if (colorlist[i] == "yellow"){ color = sf::Color::Yellow;}
                
                if (i < 3){
                    allmoney.push_back(std::make_shared<Money>(ObjectInfo<>(80,40,info.getX() + 400 - 120*(3-i)  , info.getY() + 350 - 100), color, 1500));
                }
                else if ( i >= 3){
                    allmoney.push_back(std::make_shared<Money>(ObjectInfo<>(80,40,info.getX() + 400 - 120*(3-(i - 3))  , info.getY() + 350 - 50), color , 1500));
                }}}

        void setMoney( int player, int new_money){
            allmoney[player]->setMoney(new_money);
        }

};


#endif